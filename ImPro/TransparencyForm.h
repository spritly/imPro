/****************************************************************************** 
** @Filename:	TransperencyForm.h
** @Project: 	"Bildbearbeitung"
** @author:		B.Hentzschel 
** @letzte Ae:	2012-10-25
** 
** GUI zur Erzeugung/Darstellung eines transparenten Bildes
******************************************************************************/
#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace ImPro {

	public ref class TransparencyForm : public System::Windows::Forms::Form{
	public:
		TransparencyForm(void){
			InitializeComponent();
			init();
		}

	protected:
		~TransparencyForm(){
			if (components){
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^  gBTransparency;
	protected: 
	private: System::Windows::Forms::TextBox^  tboxTranspVal;
	private: System::Windows::Forms::TrackBar^  tbTranspSlider;
	private: System::Windows::Forms::SplitContainer^  splitConImages;
	private: System::Windows::Forms::GroupBox^  gbOrgImg;
	private: System::Windows::Forms::PictureBox^  pbOrgImg;
	private: System::Windows::Forms::GroupBox^  gBOutImg;
	private: System::Windows::Forms::PictureBox^  pbOutImg;
	private: System::Windows::Forms::Button^  btCancel;
	private: System::Windows::Forms::Button^  btOK;

	private:
		System::ComponentModel::Container ^components;
		int mTranspVal;

	public:
		Bitmap^ mOutImg; 
		Bitmap^ mTmpImg;
		Bitmap^ mInImg;
		Windows::Forms::Cursor^ normalCursor;

		property Bitmap^ OutImg{
			Bitmap^ get(){
				return mOutImg;
			}
		}

		property Bitmap^ InImg{
			void set(Bitmap^ aImg){
				mInImg = aImg;
			}
		}

	private:
		void init(){
			mTranspVal = 0;
			mOutImg = nullptr;
			mTmpImg = nullptr;	
			mInImg  = nullptr;	 
			normalCursor = Windows::Forms::Cursor::Current;
		}

		void applyChanges(){
			mOutImg = mTmpImg;
		}

		void refreshTransparency(){
			mTranspVal = tbTranspSlider->Value;
			tboxTranspVal->Text = mTranspVal.ToString();
		}

		void showWaitCursor(){
			System::Windows::Forms::Cursor::Current = Cursors::WaitCursor;
		}

		void resetWaitCursor(){
			System::Windows::Forms::Cursor::Current = normalCursor;
		}

		void makeTransparencyImage(){
			refreshTransparency();
			showWaitCursor();

			mTmpImg = gcnew Bitmap(mInImg->Width, mInImg->Height);
			Color col;
			for( int x = 0; x < mInImg->Width; x++){
				for( int y = 0; y < mInImg->Height; y ++){
					col = mInImg->GetPixel(x, y );
					col = Color::FromArgb( mTranspVal, col.R, col.G, col.B);
					mTmpImg->SetPixel( x, y, col );
				}

			}
			pbOutImg->Image = mTmpImg;
			resetWaitCursor();
		}

#pragma region Windows Form Designer generated code
		void InitializeComponent(void){
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(TransparencyForm::typeid));
			this->gBTransparency = (gcnew System::Windows::Forms::GroupBox());
			this->tboxTranspVal = (gcnew System::Windows::Forms::TextBox());
			this->tbTranspSlider = (gcnew System::Windows::Forms::TrackBar());
			this->splitConImages = (gcnew System::Windows::Forms::SplitContainer());
			this->gbOrgImg = (gcnew System::Windows::Forms::GroupBox());
			this->pbOrgImg = (gcnew System::Windows::Forms::PictureBox());
			this->gBOutImg = (gcnew System::Windows::Forms::GroupBox());
			this->pbOutImg = (gcnew System::Windows::Forms::PictureBox());
			this->btCancel = (gcnew System::Windows::Forms::Button());
			this->btOK = (gcnew System::Windows::Forms::Button());
			this->gBTransparency->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tbTranspSlider))->BeginInit();
			this->splitConImages->Panel1->SuspendLayout();
			this->splitConImages->Panel2->SuspendLayout();
			this->splitConImages->SuspendLayout();
			this->gbOrgImg->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pbOrgImg))->BeginInit();
			this->gBOutImg->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pbOutImg))->BeginInit();
			this->SuspendLayout();
			// 
			// gBTransparency
			// 
			this->gBTransparency->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->gBTransparency->Controls->Add(this->tboxTranspVal);
			this->gBTransparency->Controls->Add(this->tbTranspSlider);
			this->gBTransparency->Location = System::Drawing::Point(14, 340);
			this->gBTransparency->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->gBTransparency->Name = L"gBTransparency";
			this->gBTransparency->Padding = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->gBTransparency->Size = System::Drawing::Size(805, 82);
			this->gBTransparency->TabIndex = 18;
			this->gBTransparency->TabStop = false;
			this->gBTransparency->Text = L"Transparenz";
			// 
			// tboxTranspVal
			// 
			this->tboxTranspVal->Location = System::Drawing::Point(7, 37);
			this->tboxTranspVal->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->tboxTranspVal->Name = L"tboxTranspVal";
			this->tboxTranspVal->ReadOnly = true;
			this->tboxTranspVal->Size = System::Drawing::Size(76, 20);
			this->tboxTranspVal->TabIndex = 1;
			// 
			// tbTranspSlider
			// 
			this->tbTranspSlider->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->tbTranspSlider->Location = System::Drawing::Point(100, 32);
			this->tbTranspSlider->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->tbTranspSlider->Maximum = 255;
			this->tbTranspSlider->Name = L"tbTranspSlider";
			this->tbTranspSlider->Size = System::Drawing::Size(689, 42);
			this->tbTranspSlider->TabIndex = 0;
			this->tbTranspSlider->TickFrequency = 5;
			this->tbTranspSlider->Scroll += gcnew System::EventHandler(this, &TransparencyForm::tbTranspSlider_Scroll);
			// 
			// splitConImages
			// 
			this->splitConImages->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->splitConImages->Location = System::Drawing::Point(14, 11);
			this->splitConImages->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->splitConImages->Name = L"splitConImages";
			// 
			// splitConImages.Panel1
			// 
			this->splitConImages->Panel1->Controls->Add(this->gbOrgImg);
			// 
			// splitConImages.Panel2
			// 
			this->splitConImages->Panel2->Controls->Add(this->gBOutImg);
			this->splitConImages->Size = System::Drawing::Size(806, 312);
			this->splitConImages->SplitterDistance = 405;
			this->splitConImages->SplitterWidth = 3;
			this->splitConImages->TabIndex = 17;
			// 
			// gbOrgImg
			// 
			this->gbOrgImg->Controls->Add(this->pbOrgImg);
			this->gbOrgImg->Dock = System::Windows::Forms::DockStyle::Fill;
			this->gbOrgImg->Location = System::Drawing::Point(0, 0);
			this->gbOrgImg->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->gbOrgImg->Name = L"gbOrgImg";
			this->gbOrgImg->Padding = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->gbOrgImg->Size = System::Drawing::Size(405, 312);
			this->gbOrgImg->TabIndex = 0;
			this->gbOrgImg->TabStop = false;
			this->gbOrgImg->Text = L"vorher";
			// 
			// pbOrgImg
			// 
			this->pbOrgImg->BackColor = System::Drawing::Color::Black;
			this->pbOrgImg->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pbOrgImg->Location = System::Drawing::Point(2, 15);
			this->pbOrgImg->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->pbOrgImg->Name = L"pbOrgImg";
			this->pbOrgImg->Size = System::Drawing::Size(401, 295);
			this->pbOrgImg->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pbOrgImg->TabIndex = 0;
			this->pbOrgImg->TabStop = false;
			// 
			// gBOutImg
			// 
			this->gBOutImg->Controls->Add(this->pbOutImg);
			this->gBOutImg->Dock = System::Windows::Forms::DockStyle::Fill;
			this->gBOutImg->Location = System::Drawing::Point(0, 0);
			this->gBOutImg->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->gBOutImg->Name = L"gBOutImg";
			this->gBOutImg->Padding = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->gBOutImg->Size = System::Drawing::Size(398, 312);
			this->gBOutImg->TabIndex = 0;
			this->gBOutImg->TabStop = false;
			this->gBOutImg->Text = L"nachher";
			// 
			// pbOutImg
			// 
			this->pbOutImg->BackColor = System::Drawing::Color::Black;
			this->pbOutImg->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pbOutImg->Location = System::Drawing::Point(2, 15);
			this->pbOutImg->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->pbOutImg->Name = L"pbOutImg";
			this->pbOutImg->Size = System::Drawing::Size(394, 295);
			this->pbOutImg->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pbOutImg->TabIndex = 0;
			this->pbOutImg->TabStop = false;
			// 
			// btCancel
			// 
			this->btCancel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->btCancel->Location = System::Drawing::Point(613, 436);
			this->btCancel->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->btCancel->Name = L"btCancel";
			this->btCancel->Size = System::Drawing::Size(96, 25);
			this->btCancel->TabIndex = 16;
			this->btCancel->Text = L"Abbrechen";
			this->btCancel->UseVisualStyleBackColor = true;
			this->btCancel->Click += gcnew System::EventHandler(this, &TransparencyForm::btCancel_Click);
			// 
			// btOK
			// 
			this->btOK->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btOK->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->btOK->Location = System::Drawing::Point(722, 436);
			this->btOK->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->btOK->Name = L"btOK";
			this->btOK->Size = System::Drawing::Size(96, 25);
			this->btOK->TabIndex = 15;
			this->btOK->Text = L"OK";
			this->btOK->UseVisualStyleBackColor = true;
			this->btOK->Click += gcnew System::EventHandler(this, &TransparencyForm::btOK_Click);
			// 
			// TransparencyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(835, 474);
			this->Controls->Add(this->gBTransparency);
			this->Controls->Add(this->splitConImages);
			this->Controls->Add(this->btCancel);
			this->Controls->Add(this->btOK);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->Name = L"TransparencyForm";
			this->Text = L"Transparenz";
			this->Shown += gcnew System::EventHandler(this, &TransparencyForm::TransparencyForm_Shown);
			this->gBTransparency->ResumeLayout(false);
			this->gBTransparency->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tbTranspSlider))->EndInit();
			this->splitConImages->Panel1->ResumeLayout(false);
			this->splitConImages->Panel2->ResumeLayout(false);
			this->splitConImages->ResumeLayout(false);
			this->gbOrgImg->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pbOrgImg))->EndInit();
			this->gBOutImg->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pbOutImg))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

		void tbTranspSlider_Scroll( Object^  sender, EventArgs^  e) {
			makeTransparencyImage();
		}

		void TransparencyForm_Shown(Object^  sender, EventArgs^  e) {
			tbTranspSlider->Value = tbTranspSlider->Minimum;
			refreshTransparency();
			pbOutImg->Image = nullptr;
			if( mInImg ){
				pbOrgImg->Image = mInImg;
			}else{
				pbOrgImg->Image = nullptr;				
				MessageBox::Show( "Kein Bild geladen","Fehler Eingangsbild",
					MessageBoxButtons::OK, MessageBoxIcon::Stop);
				Close();
			}
		}

		void btOK_Click(Object^  sender, EventArgs^  e) {
			applyChanges();
		}

		void btCancel_Click(Object^  sender, EventArgs^  e) {
			Close();
		}
};
}
