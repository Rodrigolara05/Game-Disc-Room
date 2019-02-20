#ifndef __JUGADOR_H__
#define __JUGADOR_H__
using namespace System::Drawing;
enum Direcciones{Ninguna,Abajo,Arriba,Izquierda,Derecha};
class CJugador
{
public:
	CJugador(int x, int y){
		this->x = x;
		this->y = y;
		dx = 0;
		dy = 0;
		ultimaTecla = Abajo;
		direccion = Ninguna;
		ancho = 25;
		alto = 39;
		indiceX = 0;
		indiceY = 0;
	}
	~CJugador(){}
	Direcciones direccion;
	Rectangle getRectangulo() {
		return Rectangle(x, y, ancho, alto);
	}
	void setX(int v) { x = v; }
	void setY(int v) { y = v; }

	int getX() {return x;}
	int getY() {return y;}
	
	void dibujar(Graphics^g, Bitmap^bmp) {
		Rectangle porcionAUsar = Rectangle(indiceX*ancho, indiceY*alto, ancho, alto);
		Rectangle aumentoPersonaje = Rectangle(x, y, ancho, alto);
		g->DrawImage(bmp, aumentoPersonaje, porcionAUsar, GraphicsUnit::Pixel);
		x += dx;
		y += dy;
	}

	void mover(Graphics^g, Bitmap^bmp) {
		switch (direccion)
		{
		case Ninguna:
			dx = 0;
			dy = 0;
			switch (ultimaTecla)
			{
			case Abajo:
				indiceX = 0;
				indiceY = 0;
				break;
			case Arriba:
				indiceX = 2;
				indiceY = 0;
				break;
			case Izquierda:
				indiceX = 1;
				indiceY = 0;
				break;
			case Derecha:
				indiceX = 3;
				indiceY = 0;
				break;
			}
			break;
		case Abajo:
			indiceX = 0;
			if (indiceY >= 0 && indiceY < 2)
				indiceY++;
			else
				indiceY = 0;
			dx = 0;
			dy = 10;
			ultimaTecla = Abajo;
			break;
		case Arriba:
			indiceX = 2;
			if (indiceY >= 0 && indiceY < 2)
				indiceY++;
			else
				indiceY = 0;
			dx = 0;
			dy = -10;
			ultimaTecla = Arriba;
			break;
		case Izquierda:
			indiceX = 1;
			if (indiceY >= 0 && indiceY < 2)
				indiceY++;
			else
				indiceY = 0;
			dx = -10;
			dy = 0;
			ultimaTecla = Izquierda;
			break;
		case Derecha:
			indiceX = 3;
			if (indiceY >= 0 && indiceY < 2)
				indiceY++;
			else
				indiceY = 0;
			dx = 10;
			dy = 0;
			ultimaTecla = Derecha;
			break;
		}
		dibujar(g, bmp);
	}
private:
	//Posicion
	int x;
	int y;
	//Velocidad
	int dx;
	int dy;
	//tamaño
	int ancho;
	int alto;
	//Animacion
	int indiceX;
	int indiceY;
	//Direccion
	Direcciones ultimaTecla;
};


#endif // !__JUGADOR_H__
