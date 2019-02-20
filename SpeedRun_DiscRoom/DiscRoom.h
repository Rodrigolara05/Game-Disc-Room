#pragma once
#include "Controladora.h"
namespace SpeedRun_DiscRoom {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for DiscRoom
	/// </summary>
	public ref class DiscRoom : public System::Windows::Forms::Form
	{
	public:
		DiscRoom(void)
		{
			InitializeComponent();
			oControladora = gcnew CControladora();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DiscRoom()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^  timer1;
	protected:
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::Timer^  Creacion_de_discos;

	private:
		/// <summary>
		/// Required designer variable.
		CControladora ^oControladora;
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->Creacion_de_discos = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &DiscRoom::timer1_Tick);
			// 
			// Creacion_de_discos
			// 
			this->Creacion_de_discos->Enabled = true;
			this->Creacion_de_discos->Interval = 2500;
			this->Creacion_de_discos->Tick += gcnew System::EventHandler(this, &DiscRoom::Creacion_de_discos_Tick);
			// 
			// DiscRoom
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(684, 661);
			this->Name = L"DiscRoom";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"DiscRoom";
			this->Load += gcnew System::EventHandler(this, &DiscRoom::DiscRoom_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &DiscRoom::DiscRoom_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &DiscRoom::DiscRoom_KeyUp);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		Graphics^g = this->CreateGraphics();
		BufferedGraphicsContext^espacio = BufferedGraphicsManager::Current;
		BufferedGraphics^buffer = espacio->Allocate(g, this->ClientRectangle);

		oControladora->timer(buffer->Graphics,Creacion_de_discos);

		buffer->Render(g);
		delete buffer;
		delete espacio;
		delete g;

		//Texto de titulo
		this->Text = "Invulnerabilidad: " + oControladora->getCont_invulnerable() + " Vidas: "+oControladora->getVidas()
			+ " Nivel: " + oControladora->getNivel();
	}
	private: System::Void DiscRoom_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		switch (e->KeyCode)
		{
		case Keys::Up:
			oControladora->getoJugador()->direccion = Direcciones::Arriba;
			break;
		case Keys::Down:
			oControladora->getoJugador()->direccion = Direcciones::Abajo;
			break;
		case Keys::Left:
			oControladora->getoJugador()->direccion = Direcciones::Izquierda;
			break;
		case Keys::Right:
			oControladora->getoJugador()->direccion = Direcciones::Derecha;
			break;
		case Keys::C:
			oControladora->getoArrDisco()->disminuir_Velocidades(2); //Velocidad de 2 para los discos
		default:
			break;
		}
	}
	private: System::Void DiscRoom_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		switch (e->KeyCode)
		{
		case Keys::Up:
		case Keys::Down:
		case Keys::Left:
		case Keys::Right:
			oControladora->getoJugador()->direccion = Direcciones::Ninguna;
			break;
		case Keys::C:
			oControladora->getoArrDisco()->regresar_Velocidades();
			break;
		default:
			break;
		}
		
	}
	private: System::Void Creacion_de_discos_Tick(System::Object^  sender, System::EventArgs^  e) {
		oControladora->crear_discos(this->Width, this->Height, Creacion_de_discos);
	}
private: System::Void DiscRoom_Load(System::Object^  sender, System::EventArgs^  e) {
	oControladora->pasar_nivel(this->Width, this->Height);
}
};
}
