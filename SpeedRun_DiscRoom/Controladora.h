#ifndef __CONTROLADORA_H__
#define __CONTROLADORA_H__
#include "Jugador.h"
#include "ArrDisco.h"
using namespace System::Windows::Forms;
ref class CControladora
{
public:
	CControladora(){
		oJugador = new CJugador(110, 110);
		oArrDisco = new CArrDisco();
		bmpJugador = gcnew Bitmap("Imagenes\\Jugador.png");
		bmpEscenario_Base = gcnew Bitmap("Imagenes\\Base_Mapa_1.1.jpg");
		bmpEscenario_Marco = gcnew Bitmap("Imagenes\\Borde_Mapa_1.1.png");
		bmpDisco = gcnew Bitmap("Imagenes\\Disco2.png");
		bmpSangre = gcnew Bitmap("Imagenes\\Sangre.png");

		//Hacemos transparencia
		bmpDisco->MakeTransparent(bmpDisco->GetPixel(0, 0));
		bmpSangre->MakeTransparent(bmpDisco->GetPixel(0, 0));
		//A penas inicia se crean discos
		interruptor_crear_discos = true;
		choque = false;
		// Para la sangre
		porcionAUsar = Rectangle(0, 0, bmpSangre->Width, bmpSangre->Height);
		invulnerabilidad = false;//Porque no ha habido choque
		cont_invulnerable = 0;//X2
		nivel = 1;
		vidas = 3;
		tiempo = 0;
		tiempo_mapa = 0;	
	}
	~CControladora(){}
	CJugador*getoJugador() {
		return oJugador;
	}
	CArrDisco*getoArrDisco() {
		return oArrDisco;
	}
	void iniciar(int w, int h) {
		oArrDisco->crear_Disco_Principal(w, h);
	}
	void pasar_nivel(int w, int h) {
		oArrDisco->eliminarTodo();
		oArrDisco->crear_Disco_Principal(w,h);
		switch (nivel)
		{
		case 1:
			tiempo_mapa = 20 * 10;
			cantidad_total_discos = 5;
			//Bitmap
			bmpDisco = gcnew Bitmap("Imagenes\\Disco2.png");
			bmpDisco->MakeTransparent(bmpDisco->GetPixel(0, 0));
			bmpEscenario_Base = gcnew Bitmap("Imagenes\\Base_Mapa_1.1.jpg");
			bmpEscenario_Marco = gcnew Bitmap("Imagenes\\Borde_Mapa_1.1.png");
			break;
		case 2:
			tiempo_mapa = 30 * 10;
			cantidad_total_discos = 7;
			//Bitmap
			bmpDisco = gcnew Bitmap("Imagenes\\Disco2.png");
			bmpDisco->MakeTransparent(bmpDisco->GetPixel(0, 0));
			bmpEscenario_Base = gcnew Bitmap("Imagenes\\Base_Mapa_1.2.jpg");
			bmpEscenario_Marco = gcnew Bitmap("Imagenes\\Borde_Mapa_1.2.png");
			break;
		case 3:
			tiempo_mapa = 40 * 10;
			cantidad_total_discos = 9;
			//Bitmap
			bmpDisco = gcnew Bitmap("Imagenes\\Disco2.png");
			bmpDisco->MakeTransparent(bmpDisco->GetPixel(0, 0));
			bmpEscenario_Base = gcnew Bitmap("Imagenes\\Base_Mapa_1.3.jpg");
			bmpEscenario_Marco = gcnew Bitmap("Imagenes\\Borde_Mapa_1.3.png");
			break;
		case 4:
			tiempo_mapa = 50 * 10;
			cantidad_total_discos = 11;
			//Bitmap
			bmpDisco = gcnew Bitmap("Imagenes\\Disco2.png");
			bmpDisco->MakeTransparent(bmpDisco->GetPixel(0, 0));
			bmpEscenario_Base = gcnew Bitmap("Imagenes\\Base_Mapa_1.4.jpg");
			bmpEscenario_Marco = gcnew Bitmap("Imagenes\\Borde_Mapa_1.4.png");
			break;
		case 5:
			tiempo_mapa = 60 * 10;
			cantidad_total_discos = 13;
			//Bitmap
			bmpDisco = gcnew Bitmap("Imagenes\\Disco1.png"); //Este disco es diferente por el mapa
			bmpDisco->MakeTransparent(bmpDisco->GetPixel(0, 0));
			bmpEscenario_Base = gcnew Bitmap("Imagenes\\Base_Mapa_1.5.jpg");
			bmpEscenario_Marco = gcnew Bitmap("Imagenes\\Borde_Mapa_1.5.png");
			break;
		}
	}
	void colision_Jugador_Disco(Graphics^g) {
		for (int i = 0; i < oArrDisco->getTamaño(); i++)
		{
			//Si el jugador y el disco chocan
			if (oJugador->getRectangulo().IntersectsWith(oArrDisco->getRectangulo(i))) {
				posicion = Rectangle(oJugador->getX() - 50, oJugador->getY() - 50, bmpSangre->Width / 2, bmpSangre->Height / 2);
				choque = true;
				oJugador->setX(110);
				oJugador->setY(110);
				invulnerabilidad = true;
				vidas--;
			}
		}
	}
	void timer(Graphics^g,Timer^timer1) {
		//Para pasar de nivel
		if (tiempo == (tiempo_mapa) && nivel < 5) {
			nivel++;
			tiempo = 0;
			pasar_nivel(g->VisibleClipBounds.Width, g->VisibleClipBounds.Height);
			timer1->Enabled = true;
		}
		ancho_visible = g->VisibleClipBounds.Width;
		alto_visible = g->VisibleClipBounds.Height;
		//Primero la base
		g->DrawImage(bmpEscenario_Base, 0, 0, ancho_visible, alto_visible);

		if (invulnerabilidad == false)
			colision_Jugador_Disco(g);
		else
			cont_invulnerable++;

		if (cont_invulnerable >= 50) {
			invulnerabilidad = false;
			cont_invulnerable = 0;
		}

		if (choque == true) {
			//Dibujar la Sangre
			g->DrawImage(bmpSangre, posicion, porcionAUsar, GraphicsUnit::Pixel);
		}
		oJugador->mover(g, bmpJugador);
		oArrDisco->dibujar(g, bmpDisco);
		g->DrawImage(bmpEscenario_Marco, 0, 0, ancho_visible, alto_visible);
		tiempo++;
	}
	//Creacion de discos
	void crear_discos(int w, int h, System::Windows::Forms::Timer^timer1) {
		if (oArrDisco->getTamaño() != 0 && oArrDisco->getTamaño() % 3 == 0)
			oArrDisco->crearDiscos(w, h, Estado::Borde);
		else {
			oArrDisco->crearDiscos(w, h, Estado::Centro);
		}
		if (oArrDisco->getTamaño() == cantidad_total_discos) {
			timer1->Enabled = false;
			oArrDisco->eliminar_disco_Principal();
		}
	}
	bool getInterruptor_crear_discos() { return interruptor_crear_discos; }

	int getCont_invulnerable() { return cont_invulnerable; }
	int getVidas() { return vidas; }
	int getNivel() { return nivel; }
private:
	//Constructores
	CJugador*oJugador;
	CArrDisco*oArrDisco;
	//Bitmaps
	Bitmap^bmpJugador;
	Bitmap^bmpEscenario_Base;
	Bitmap^bmpEscenario_Marco;
	Bitmap^bmpDisco;
	Bitmap^bmpSangre;

	Rectangle posicion; Rectangle porcionAUsar;
	
	int ancho_visible;
	int alto_visible;

	bool interruptor_crear_discos;
	bool choque;
	bool invulnerabilidad;
	int cont_invulnerable;
	int nivel;
	int vidas;
	int cantidad_total_discos;
	int tiempo;
	int tiempo_mapa;
};

#endif // !__CONTROLADORA_H__
