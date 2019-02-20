#ifndef __ARRDISCO_H__
#define __ARRDISCO_H__
#include "Disco.h"
#include <vector>
using namespace std;
class CArrDisco
{
public:
	CArrDisco(){
		arreglo = vector<CDisco*>();
	}
	~CArrDisco(){}
	int getTamaño() {
		return arreglo.size();
	}
	void agregar(CDisco* nuevo) {
		arreglo.push_back(nuevo);
	}
	void eliminarTodo() {
		arreglo.clear();
	}
	void dibujar(Graphics^g, Bitmap^bmpDisco) {
		oDiscoPrincipal->dibujar(g, bmpDisco);
		for (int i = 0; i < arreglo.size(); i++)
		{
			arreglo.at(i)->dibujar(g, bmpDisco);
		}
	}
	void crear_Disco_Principal(int alto, int ancho) {
		oDiscoPrincipal = new CDisco(ancho / 2, alto / 2, 0, 0, 3, Estado::Centro);
	}
	void crearDiscos(int ancho, int alto, Estado estado) {
		Random r;
		CDisco* oDisco;
		int velocidad = r.Next(5, 10);
		int v_x= r.Next(8, 16);
		int v_y = r.Next(8, 16);
		int t = r.Next(2, 5);
		switch (r.Next(0,4)) //Para cambiar las direcciones iniciales del disco
		{
		case 0:
			v_x *= -1;
			break;
		case 1:
			v_y *= -1;
			break;
		case 2:
			v_x *= -1;
			v_y *= -1;
			break;
		case 3:
			break;
		}
		oDisco = new CDisco(ancho / 2, alto / 2, v_x, v_y, t, estado);
		agregar(oDisco);
	}
	void eliminar_disco_Principal() {
		delete oDiscoPrincipal;
	}
	void disminuir_Velocidades(int v) {
		for (int i=0 ; i < arreglo.size(); i++)
		{
			arreglo.at(i)->set_dx(v);
			arreglo.at(i)->set_dy(v);
		}
	}
	void regresar_Velocidades(){
		for (int i = 0; i < arreglo.size(); i++)
		{
			arreglo.at(i)->setDX(arreglo.at(i)->get_aux_dx());
			arreglo.at(i)->setDY(arreglo.at(i)->get_aux_dy());
		}
	}
	Rectangle getRectangulo(int i) {
		return arreglo.at(i)->getRectangulo();
	}
private:
	vector<CDisco*>arreglo;
	CDisco*oDiscoPrincipal;
};

#endif // !__ARRDISCO_H__
