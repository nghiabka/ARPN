#pragma once
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv\ml.h>
#include <opencv\cxcore.h>
#include <stdio.h>

#include "PlateFinder.h"
namespace ANPR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Summary for Mainform
	/// </summary>
	public ref class Mainform : public System::Windows::Forms::Form
	{
	private:
		IplImage *src;

	public:
		Mainform(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Mainform()
		{
			if (components)
			{
				delete components;
			}
			if (src) {
				src = NULL;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	protected:
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(74, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(486, 277);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(74, 338);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(195, 74);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox2->TabIndex = 1;
			this->pictureBox2->TabStop = false;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(298, 358);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(124, 43);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Browes...";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Mainform::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(448, 358);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(112, 43);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Recognise";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Mainform::button2_Click);
			// 
			// Mainform
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(641, 442);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"Mainform";
			this->Text = L"Mainform";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
		private: char* ConvertStringtoChar(System::String ^str)
		{
			char *str2 = (char*)(void*) Marshal ::StringToHGlobalAnsi(str);

			return str2;
		}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		OpenFileDialog^ dlg = gcnew OpenFileDialog;
		dlg->Filter = "Image (*.bmp; *.jpg; *.jpeg; *.png) |*.bmp; *.jpg; *.jpeg; *.png|All files (*.*)|*.*||";

		if (dlg->ShowDialog() != System::Windows::Forms::DialogResult::Cancel)
		{
			src = cvLoadImage(ConvertStringtoChar(dlg->FileName));

			Bitmap ^bmp = gcnew Bitmap(dlg->FileName);
			pictureBox1  ->Image = bmp;
			pictureBox1->Refresh();
		}
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		PlateFinder pf;

		if (!src)
		{
			MessageBox::Show("No image loaded", "Error", MessageBoxButtons::OK);
			return;
		}

		// resize image
		IplImage *resizeImg = cvCreateImage(cvSize(800, 600), src->depth, src->nChannels);	// Anh resize
		cvResize(src, resizeImg);

		// Convert sang anh xam
		IplImage *grayImg = cvCreateImage (cvGetSize(resizeImg), IPL_DEPTH_8U, 1);	// Anh resize
		cvCvtColor(resizeImg, grayImg, CV_RGB2GRAY);
		cvNormalize(grayImg, grayImg, 0, 255, CV_MINMAX);

		pf.ImageRestoration(grayImg);
	}
};
}
