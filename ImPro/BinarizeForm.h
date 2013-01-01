/****************************************************************************** 
** @Filename: 		BinarizeForm.h
** @Project: 		"Bildbearbeitung"
** @author:    	B.Hentzschel 
** @letzte Ae: 	2012-10-25
** 
** Gui zur Darstellung der Binarisierung eines Bildes
******************************************************************************/
#pragma once

#include "IpManager.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace ImPro {

	using namespace IMGProcessing;

	public ref class BinarizeForm : public System::Windows::Forms::Form{
	private:
		int mThreshold;

	public:
		Bitmap^ mBinImg; 
		Bitmap^ mTmpBinImg;
		IpManager^ mIpManager;
		Windows::Forms::Cursor^ normalCursor;

		BinarizeForm(void){
			InitializeComponent();
			init();
		}

		property Bitmap^ BinImg{
			// binImg darf von aussen nur abgefragt werden:
			Bitmap^ get(){
				return mBinImg;
			}
		} 

		property IpManager^ IpMan{
			IpManager^ get(){
				return mIpManager;
			}
			void set( IpManager^ aIpMan){
				mIpManager = aIpMan;
			}
		}

	private:
		void init(){
			mBinImg = nullptr;
			mTmpBinImg = nullptr;
			mIpManager = nullptr;							
			normalCursor = Windows::Forms::Cursor::Current;
		}

		void applyChanges(){
			if( mIpManager != nullptr ){
				mBinImg = mTmpBinImg;
			}
		}

		void refreshTreshold(){
			mThreshold = tbThresh->Value;
			tboxThresh->Text = mThreshold.ToString();
		}

		void showWaitCursor(){
			System::Windows::Forms::Cursor::Current = Cursors::WaitCursor;
		}

		void resetWaitCursor(){
			System::Windows::Forms::Cursor::Current = normalCursor;
		}

		// erzeugt das binarisierte Bild anhand eines Schwellwertes (per slider)
		// und zeigt es an
		void binarizeImage(){
			refreshTreshold();
			if( mIpManager ){
				showWaitCursor(); //eieruhr start
				mTmpBinImg = mIpManager->BinarizeImg( mIpManager->InImg, mThreshold );
				pbBinImg->Image = mTmpBinImg;
				resetWaitCursor();// eieruhr ende
			}
		}

	protected:
		~BinarizeForm(){
			if (components){
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btCancel;
	private: System::Windows::Forms::Button^  btOK;
	private: System::Windows::Forms::SplitContainer^  splitConImages;
	private: System::Windows::Forms::GroupBox^  gbOrgImg;
	private: System::Windows::Forms::GroupBox^  gBBinImg;
	private: System::Windows::Forms::PictureBox^  pbOrgImg;
	private: System::Windows::Forms::PictureBox^  pbBinImg;
	private: System::Windows::Forms::GroupBox^  gBThresh;
	private: System::Windows::Forms::TextBox^  tboxThresh;
	private: System::Windows::Forms::TrackBar^  tbThresh;

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void){
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(BinarizeForm::typeid));
			this->btCancel = (gcnew System::Windows::Forms::Button());
			this->btOK = (gcnew System::Windows::Forms::Button());
			this->splitConImages = (gcnew System::Windows::Forms::SplitContainer());
			this->gbOrgImg = (gcnew System::Windows::Forms::GroupBox());
			this->pbOrgImg = (gcnew System::Windows::Forms::PictureBox());
			this->gBBinImg = (gcnew System::Windows::Forms::GroupBox());
			this->pbBinImg = (gcnew System::Windows::Forms::PictureBox());
			this->gBThresh = (gcnew System::Windows::Forms::GroupBox());
			this->tboxThresh = (gcnew System::Windows::Forms::TextBox());
			this->tbThresh = (gcnew System::Windows::Forms::TrackBar());
			this->splitConImages->Panel1->SuspendLayout();
			this->splitConImages->Panel2->SuspendLayout();
			this->splitConImages->SuspendLayout();
			this->gbOrgImg->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pbOrgImg))->BeginInit();
			this->gBBinImg->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pbBinImg))->BeginInit();
			this->gBThresh->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tbThresh))->BeginInit();
			this->SuspendLayout();
			// 
			// btCancel
			// 
			this->btCancel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->btCancel->Location = System::Drawing::Point(626, 440);
			this->btCancel->Margin = System::Windows::Forms::Padding(2);
			this->btCancel->Name = L"btCancel";
			this->btCancel->Size = System::Drawing::Size(96, 25);
			this->btCancel->TabIndex = 7;
			this->btCancel->Text = L"Abbrechen";
			this->btCancel->UseVisualStyleBackColor = true;
			this->btCancel->Click += gcnew System::EventHandler(this, &BinarizeForm::btCancel_Click);
			// 
			// btOK
			// 
			this->btOK->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btOK->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->btOK->Location = System::Drawing::Point(736, 440);
			this->btOK->Margin = System::Windows::Forms::Padding(2);
			this->btOK->Name = L"btOK";
			this->btOK->Size = System::Drawing::Size(96, 25);
			this->btOK->TabIndex = 6;
			this->btOK->Text = L"OK";
			this->btOK->UseVisualStyleBackColor = true;
			this->btOK->Click += gcnew System::EventHandler(this, &BinarizeForm::btOK_Click);
			// 
			// splitConImages
			// 
			this->splitConImages->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->splitConImages->Location = System::Drawing::Point(2, 2);
			this->splitConImages->Margin = System::Windows::Forms::Padding(2);
			this->splitConImages->Name = L"splitConImages";
			// 
			// splitConImages.Panel1
			// 
			this->splitConImages->Panel1->Controls->Add(this->gbOrgImg);
			// 
			// splitConImages.Panel2
			// 
			this->splitConImages->Panel2->Controls->Add(this->gBBinImg);
			this->splitConImages->Size = System::Drawing::Size(832, 326);
			this->splitConImages->SplitterDistance = 420;
			this->splitConImages->SplitterWidth = 3;
			this->splitConImages->TabIndex = 9;
			// 
			// gbOrgImg
			// 
			this->gbOrgImg->Controls->Add(this->pbOrgImg);
			this->gbOrgImg->Dock = System::Windows::Forms::DockStyle::Fill;
			this->gbOrgImg->Location = System::Drawing::Point(0, 0);
			this->gbOrgImg->Margin = System::Windows::Forms::Padding(2);
			this->gbOrgImg->Name = L"gbOrgImg";
			this->gbOrgImg->Padding = System::Windows::Forms::Padding(2);
			this->gbOrgImg->Size = System::Drawing::Size(420, 326);
			this->gbOrgImg->TabIndex = 0;
			this->gbOrgImg->TabStop = false;
			this->gbOrgImg->Text = L"vorher";
			// 
			// pbOrgImg
			// 
			this->pbOrgImg->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pbOrgImg->Location = System::Drawing::Point(2, 15);
			this->pbOrgImg->Margin = System::Windows::Forms::Padding(2);
			this->pbOrgImg->Name = L"pbOrgImg";
			this->pbOrgImg->Size = System::Drawing::Size(416, 309);
			this->pbOrgImg->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pbOrgImg->TabIndex = 0;
			this->pbOrgImg->TabStop = false;
			// 
			// gBBinImg
			// 
			this->gBBinImg->Controls->Add(this->pbBinImg);
			this->gBBinImg->Dock = System::Windows::Forms::DockStyle::Fill;
			this->gBBinImg->Location = System::Drawing::Point(0, 0);
			this->gBBinImg->Margin = System::Windows::Forms::Padding(2);
			this->gBBinImg->Name = L"gBBinImg";
			this->gBBinImg->Padding = System::Windows::Forms::Padding(2);
			this->gBBinImg->Size = System::Drawing::Size(409, 326);
			this->gBBinImg->TabIndex = 0;
			this->gBBinImg->TabStop = false;
			this->gBBinImg->Text = L"nachher";
			// 
			// pbBinImg
			// 
			this->pbBinImg->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pbBinImg->Location = System::Drawing::Point(2, 15);
			this->pbBinImg->Margin = System::Windows::Forms::Padding(2);
			this->pbBinImg->Name = L"pbBinImg";
			this->pbBinImg->Size = System::Drawing::Size(405, 309);
			this->pbBinImg->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pbBinImg->TabIndex = 0;
			this->pbBinImg->TabStop = false;
			// 
			// gBThresh
			// 
			this->gBThresh->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->gBThresh->Controls->Add(this->tboxThresh);
			this->gBThresh->Controls->Add(this->tbThresh);
			this->gBThresh->Location = System::Drawing::Point(2, 344);
			this->gBThresh->Margin = System::Windows::Forms::Padding(2);
			this->gBThresh->Name = L"gBThresh";
			this->gBThresh->Padding = System::Windows::Forms::Padding(2);
			this->gBThresh->Size = System::Drawing::Size(830, 82);
			this->gBThresh->TabIndex = 10;
			this->gBThresh->TabStop = false;
			this->gBThresh->Text = L"Schwellwert";
			// 
			// tboxThresh
			// 
			this->tboxThresh->Location = System::Drawing::Point(7, 37);
			this->tboxThresh->Margin = System::Windows::Forms::Padding(2);
			this->tboxThresh->Name = L"tboxThresh";
			this->tboxThresh->ReadOnly = true;
			this->tboxThresh->Size = System::Drawing::Size(76, 20);
			this->tboxThresh->TabIndex = 1;
			// 
			// tbThresh
			// 
			this->tbThresh->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->tbThresh->Location = System::Drawing::Point(100, 32);
			this->tbThresh->Margin = System::Windows::Forms::Padding(2);
			this->tbThresh->Maximum = 255;
			this->tbThresh->Name = L"tbThresh";
			this->tbThresh->Size = System::Drawing::Size(715, 42);
			this->tbThresh->TabIndex = 0;
			this->tbThresh->TickFrequency = 5;
			this->tbThresh->Scroll += gcnew System::EventHandler(this, &BinarizeForm::tbThresh_Scroll);
			// 
			// BinarizeForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(835, 474);
			this->Controls->Add(this->gBThresh);
			this->Controls->Add(this->splitConImages);
			this->Controls->Add(this->btCancel);
			this->Controls->Add(this->btOK);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"BinarizeForm";
			this->Text = L"Binarisierung";
			this->Shown += gcnew System::EventHandler(this, &BinarizeForm::BinarizeForm_Shown);
			this->splitConImages->Panel1->ResumeLayout(false);
			this->splitConImages->Panel2->ResumeLayout(false);
			this->splitConImages->ResumeLayout(false);
			this->gbOrgImg->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pbOrgImg))->EndInit();
			this->gBBinImg->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pbBinImg))->EndInit();
			this->gBThresh->ResumeLayout(false);
			this->gBThresh->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tbThresh))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

		void btCancel_Click(System::Object^  sender, System::EventArgs^  e) {
			Close();
		}

		void BinarizeForm_Shown(System::Object^  sender, System::EventArgs^  e) {
			refreshTreshold();
			pbBinImg->Image = nullptr;
			if( (mIpManager ) && mIpManager->InImg ){
				// zeige orgBild in Farbe
				pbOrgImg->Image = mIpManager->InImg;
			}else{
				pbOrgImg->Image = nullptr;				
				MessageBox::Show( "Kein Bild geladen","Fehler Eingangsbild",
					MessageBoxButtons::OK, MessageBoxIcon::Stop);
				Close();
			}

		}

		void tbThresh_Scroll(System::Object^  sender, System::EventArgs^  e) {
			binarizeImage();			
		}
		void btOK_Click(System::Object^  sender, System::EventArgs^  e) {
			applyChanges();
		}
};
}
