#ifndef __Disco_h__
#define __Disco_h__
using namespace System::Drawing;
using namespace System;
enum Estado{Borde, Centro};
class CDisco
{
public:
	CDisco(){
		pos = 0;
		ancho = 0;
		alto = 0;
		x = 0;
		y = 0;
		dx = 0;
		dy = 0;
		aux_dx = 0;
		aux_dy = 0;
		indiceX = 0;
		indiceY = 0;
		reducir_tamaño = 0;
	}
	CDisco(int x, int y, int dx, int dy, int reducir_tamaño, Estado estado) {
		Random r;
		pos = 0;
		ancho = 374/2;
		alto = 558/3;
		this->x = (x - ((ancho / reducir_tamaño) / 2 - (78 / reducir_tamaño) / 2));
		this->y = (y - ((alto / reducir_tamaño) / 2 - (79 / reducir_tamaño) / 2));
		this->dx = dx;
		this->dy = dy;
		aux_dx = dx;
		aux_dy = dy;
		indiceX = 0;
		indiceY = 0;
		this->reducir_tamaño = reducir_tamaño;
		this->estado = estado;
		if (this->estado == Estado::Borde) {
			this->x = 39;
			this->y = 36;
			this->dx = 5;
			this->dy = 5;
			this->reducir_tamaño = 3;
		}
		limite = r.Next(10, 50);
		X = 0;
		Y = 0;
		X2 = 0;
	}
	~CDisco(){}
	void animar() {
		if (indiceX == 0 && indiceY == 0)
			indiceX++;
		else {
			if (indiceX == 1 && indiceY == 0) {
				indiceX = 0;
				indiceY++;
			}
			else {
				if (indiceX == 0 && indiceY == 1)
					indiceX++;
				else {
					if (indiceX == 1 && indiceY == 1) {
						indiceX = 0;
						indiceY++;
					}
					else {
						if (indiceX == 0 && indiceY == 2)
							indiceX++;
						else {
							if (indiceX == 1 && indiceY == 2) {
								indiceX = 0;
								indiceY = 0;
							}
						}
					}
				}
			}
		}
	}
	void mover(Graphics^g) {
		//Rebote en los bordes
		if (x + dx <= 60 || x + (ancho / reducir_tamaño) + dx >= ((g->VisibleClipBounds.Width) - 70))
			dx *= -1;
		if (y + dy <= 58 || y + (alto / reducir_tamaño) + dy >= ((g->VisibleClipBounds.Height) - 65))
			dy *= -1;
		x += dx;
		y += dy;
	}
	void mover_borde() {
		//Mover por los bordes
		if (x == 39 && y == 36)
			pos = 0;
		if (x >= 581 && y == 36) {
			pos = 1;
			X = x;
		}
		if (x == X && y >= 565) {
			pos = 2;
			Y = y;
		}
		if (x <= 39 && y == Y) {
			pos = 3;
			X2 = 2;
		}
		if (x == X2 && y <= 36) {
			pos = 0;
			y = 36;
		}
		if (pos == 0)//Arriba
			x += dx;
		if (pos == 1)//Derecha
			y += dy;
		if (pos == 2)//Abajo
			x -= dx;
		if (pos == 3)//Izquierda
			y -= dy;
	}
	//Diferenciar movimiento de discos
	void mover_dos(Graphics^g) {
		if (estado == Estado::Centro)
			mover(g);
		else {
			if (estado == Estado::Borde)
				mover_borde();
		}
	}
	void dibujar(Graphics^g, Bitmap^bmpDisco) {
		Rectangle porcionAusar = Rectangle(indiceX*ancho, indiceY*alto, ancho, alto);
		Rectangle tamaño = Rectangle(x, y, ancho / reducir_tamaño, alto / reducir_tamaño);
		g->DrawImage(bmpDisco, tamaño, porcionAusar, GraphicsUnit::Pixel);
		mover_dos(g);
		animar();
	}
	void set_dx(int v) {
		if (dx < 0) { //Si va para la izquierda
			if (v < 0)
				dx = v;
			else
				dx = v*-1;
		}
		if(dx > 0) { //Si va para la derecha
			if (v > 0)
				dx = v;
			else
				dx = v*-1;
		}
	}
	void set_dy(int v) {
		if (dy < 0) { //Si va para la izquierda
			if (v < 0)
				dy = v;
			else
				dy = v*-1;
		}
		if (dy > 0) { //Si va para la derecha
			if (v > 0)
				dy = v;
			else
				dy = v*-1;
		}
	}
	void setDX(int v) {
		if (dx < 0) { //Si va para la izquierda
			if (v < 0)
				dx = v;
			else
				dx = v*-1;
		}
		if (dx > 0) { //Si va para la derecha
			if (v > 0)
				dx = v;
			else
				dx = v*-1;
		}
	}
	void setDY(int v) {
		if (dy < 0) { //Si va para la izquierda
			if (v < 0)
				dy = v;
			else
				dy = v*-1;
		}
		if (dy > 0) { //Si va para la derecha
			if (v > 0)
				dy = v;
			else
				dy = v*-1;
		}
	}
	int get_aux_dx() {
		return aux_dx;
	}
	int get_aux_dy() {
		return aux_dy;
	}
	Rectangle getRectangulo() {
		return Rectangle(x, y, ancho / reducir_tamaño, alto / reducir_tamaño);
	}
private:
	int x;
	int y;
	int dx;
	int dy;
	int ancho;
	int alto;
	int indiceX, indiceY;
	int reducir_tamaño;
	Estado estado;
	int aux_dx;
	int aux_dy;
	// Para el disco bordeante
	int limite;
	int pos;
	int X;
	int Y;
	int X2;
};


#endif // !__Disco_h__
