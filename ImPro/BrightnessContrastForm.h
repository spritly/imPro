/****************************************************************************** 
** @Filename:	BrightnessContrastForm.h
** @Project: 	"Bildbearbeitung"
** @author:		B.Hentzschel 
** @letzte Ae:	2012-10-25
** 
** GUI um Helligkeit und Kontrast eines Bildes einzustellen 
******************************************************************************/
#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace ImPro {

	public ref class BrightnessContrastForm : public System::Windows::Forms::Form{
	public:
		BrightnessContrastForm(void){
			InitializeComponent();
			init();
		}

	protected:
		~BrightnessContrastForm(){
			if (components){
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^  gBOutImg;
	protected: 
	private: System::Windows::Forms::PictureBox^  pbOutImg;
	private: System::Windows::Forms::GroupBox^  gbBrigthness;
	private: System::Windows::Forms::TextBox^  tboxBrightnessVal;
	private: System::Windows::Forms::TrackBar^  tbBrightnessSlider;
	private: System::Windows::Forms::PictureBox^  pbOrgImg;
	private: System::Windows::Forms::Button^  btCancel;
	private: System::Windows::Forms::GroupBox^  gbOrgImg;
	private: System::Windows::Forms::SplitContainer^  splitConImages;
	private: System::Windows::Forms::Button^  btOK;
	private: System::Windows::Forms::GroupBox^  gbContrast;
	private: System::Windows::Forms::TextBox^  tboxContrastVal;
	private: System::Windows::Forms::TrackBar^  tbContrastSlider;

	private:
		System::ComponentModel::Container ^components;
		int mBrightness;
		float	mContrast;
	public:
		Bitmap^ mOutImg; 
		Bitmap^ mTmpImg;
		Bitmap^ mInImg;
	private: System::Windows::Forms::Button^  btApplyContrast;
	public: 
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
		void init(){
			mBrightness = 0;
			mContrast = 0.0;
			mOutImg = nullptr;
			mTmpImg = nullptr;	
			mInImg  = nullptr;	 
			normalCursor = Windows::Forms::Cursor::Current;
		}

		void showWaitCursor(){
			System::Windows::Forms::Cursor::Current = Cursors::WaitCursor;
		}
		void resetWaitCursor(){
			System::Windows::Forms::Cursor::Current = normalCursor;
		}
		void applyChanges(){
			mOutImg = mTmpImg;
		}
		void refreshBrightness(){
			mBrightness = tbBrightnessSlider->Value;
			tboxBrightnessVal->Text = mBrightness.ToString();
		}
		void refreshContrast(){
			mContrast = (float)tbContrastSlider->Value/10;
			tboxContrastVal->Text = mContrast.ToString();
		}
		
		// erzeugt aus eingangsbild ein neues Bild unter Beruecksichtigung
		// des neuen Kontrastwertes (slider)
		void changeContrastOfImg(){	
			refreshContrast();
			float AvgR, AvgG, AvgB;
			long int sumR, sumG, sumB;			
			int pixCount  =  mInImg->Width * mInImg->Height;
			int rVal, gVal, bVal, x, y;

			sumR = sumG = sumB = 0;
			AvgR = AvgG = AvgB = 0.0;
			rVal, gVal, bVal = 0;

			showWaitCursor();

			if( !pixCount )
				return;

			mTmpImg = gcnew Bitmap(mInImg->Width, mInImg->Height);
			Color col;
			for( x = 0; x < mInImg->Width; x++){
				for( y = 0; y < mInImg->Height; y ++){
					col = mInImg->GetPixel(x, y );
					sumR += col.R;
					sumG += col.G;
					sumB += col.B;
				}
			}
			AvgR = (float) sumR / (float) pixCount; 
			AvgG = (float) sumG / (float) pixCount; 
			AvgB = (float) sumB / (float) pixCount; 

			for( x = 0; x < mInImg->Width; x++){
				for( y = 0; y < mInImg->Height; y ++){
					col = mInImg->GetPixel(x, y );
					rVal = (int)(mContrast * ((float)col.R - AvgR) + AvgR); 
					gVal = (int)(mContrast * ((float)col.G - AvgG) + AvgG); 
					bVal = (int)(mContrast * ((float)col.B - AvgB) + AvgB); 
					col = Color::FromArgb( 	
								rVal > 255 ? 255 : (rVal < 0 ? 0 : rVal),
								gVal > 255 ? 255 : (gVal < 0 ? 0 : gVal), 
								bVal > 255 ? 255 : (bVal < 0 ? 0 : bVal) );
					mTmpImg->SetPixel( x, y, col );
				}
			}
			pbOutImg->Image = mTmpImg;
			resetWaitCursor();
		} // changeContrastOfImg

		// erzeugt aus eingangsbild ein neues Bild unter Beruecksichtigung
		// des neuen Helligkeitswertes (slider)
		void changeBrightnessOfImg(){
			int rVal, gVal, bVal;
			Color col;
			refreshBrightness();
			showWaitCursor();	

			mTmpImg = gcnew Bitmap(mInImg->Width, mInImg->Height);
			for( int x = 0; x < mInImg->Width; x++){
				for( int y = 0; y < mInImg->Height; y ++){
					col = mInImg->GetPixel(x, y );
					rVal = col.R + mBrightness;
					gVal = col.G + mBrightness;
					bVal = col.B + mBrightness;

					col = Color::FromArgb(
								rVal > 255 ? 255 : (rVal < 0 ? 0 : rVal), 
								gVal > 255 ? 255 : (gVal < 0 ? 0 : gVal), 
								bVal > 255 ? 255 : (bVal < 0 ? 0 : bVal) );

					mTmpImg->SetPixel( x, y, col );
				}

			}
			pbOutImg->Image = mTmpImg;
			resetWaitCursor();
		}

#pragma region Windows Form Designer generated code
		void InitializeComponent(void){
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(BrightnessContrastForm::typeid));
			this->gBOutImg = (gcnew System::Windows::Forms::GroupBox());
			this->pbOutImg = (gcnew System::Windows::Forms::PictureBox());
			this->gbBrigthness = (gcnew System::Windows::Forms::GroupBox());
			this->tboxBrightnessVal = (gcnew System::Windows::Forms::TextBox());
			this->tbBrightnessSlider = (gcnew System::Windows::Forms::TrackBar());
			this->pbOrgImg = (gcnew System::Windows::Forms::PictureBox());
			this->btCancel = (gcnew System::Windows::Forms::Button());
			this->gbOrgImg = (gcnew System::Windows::Forms::GroupBox());
			this->splitConImages = (gcnew System::Windows::Forms::SplitContainer());
			this->btOK = (gcnew System::Windows::Forms::Button());
			this->gbContrast = (gcnew System::Windows::Forms::GroupBox());
			this->tboxContrastVal = (gcnew System::Windows::Forms::TextBox());
			this->tbContrastSlider = (gcnew System::Windows::Forms::TrackBar());
			this->btApplyContrast = (gcnew System::Windows::Forms::Button());
			this->gBOutImg->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pbOutImg))->BeginInit();
			this->gbBrigthness->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tbBrightnessSlider))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pbOrgImg))->BeginInit();
			this->gbOrgImg->SuspendLayout();
			this->splitConImages->Panel1->SuspendLayout();
			this->splitConImages->Panel2->SuspendLayout();
			this->splitConImages->SuspendLayout();
			this->gbContrast->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tbContrastSlider))->BeginInit();
			this->SuspendLayout();
			// 
			// gBOutImg
			// 
			this->gBOutImg->Controls->Add(this->pbOutImg);
			this->gBOutImg->Dock = System::Windows::Forms::DockStyle::Fill;
			this->gBOutImg->Location = System::Drawing::Point(0, 0);
			this->gBOutImg->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->gBOutImg->Name = L"gBOutImg";
			this->gBOutImg->Padding = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->gBOutImg->Size = System::Drawing::Size(398, 340);
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
			this->pbOutImg->Size = System::Drawing::Size(394, 323);
			this->pbOutImg->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pbOutImg->TabIndex = 0;
			this->pbOutImg->TabStop = false;
			// 
			// gbBrigthness
			// 
			this->gbBrigthness->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->gbBrigthness->Controls->Add(this->tboxBrightnessVal);
			this->gbBrigthness->Controls->Add(this->tbBrightnessSlider);
			this->gbBrigthness->Location = System::Drawing::Point(14, 466);
			this->gbBrigthness->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->gbBrigthness->Name = L"gbBrigthness";
			this->gbBrigthness->Padding = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->gbBrigthness->Size = System::Drawing::Size(805, 82);
			this->gbBrigthness->TabIndex = 22;
			this->gbBrigthness->TabStop = false;
			this->gbBrigthness->Text = L"Helligkeit";
			// 
			// tboxBrightnessVal
			// 
			this->tboxBrightnessVal->Location = System::Drawing::Point(7, 37);
			this->tboxBrightnessVal->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->tboxBrightnessVal->Name = L"tboxBrightnessVal";
			this->tboxBrightnessVal->ReadOnly = true;
			this->tboxBrightnessVal->Size = System::Drawing::Size(76, 20);
			this->tboxBrightnessVal->TabIndex = 1;
			// 
			// tbBrightnessSlider
			// 
			this->tbBrightnessSlider->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->tbBrightnessSlider->Location = System::Drawing::Point(100, 32);
			this->tbBrightnessSlider->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->tbBrightnessSlider->Maximum = 255;
			this->tbBrightnessSlider->Name = L"tbBrightnessSlider";
			this->tbBrightnessSlider->Size = System::Drawing::Size(689, 42);
			this->tbBrightnessSlider->TabIndex = 0;
			this->tbBrightnessSlider->TickFrequency = 5;
			this->tbBrightnessSlider->Scroll += gcnew System::EventHandler(this, &BrightnessContrastForm::tbBrightnessSlider_Scroll);
			// 
			// pbOrgImg
			// 
			this->pbOrgImg->BackColor = System::Drawing::Color::Black;
			this->pbOrgImg->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pbOrgImg->Location = System::Drawing::Point(2, 15);
			this->pbOrgImg->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->pbOrgImg->Name = L"pbOrgImg";
			this->pbOrgImg->Size = System::Drawing::Size(401, 323);
			this->pbOrgImg->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pbOrgImg->TabIndex = 0;
			this->pbOrgImg->TabStop = false;
			// 
			// btCancel
			// 
			this->btCancel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->btCancel->Location = System::Drawing::Point(613, 562);
			this->btCancel->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->btCancel->Name = L"btCancel";
			this->btCancel->Size = System::Drawing::Size(96, 25);
			this->btCancel->TabIndex = 20;
			this->btCancel->Text = L"Abbrechen";
			this->btCancel->UseVisualStyleBackColor = true;
			this->btCancel->Click += gcnew System::EventHandler(this, &BrightnessContrastForm::btCancel_Click);
			// 
			// gbOrgImg
			// 
			this->gbOrgImg->Controls->Add(this->pbOrgImg);
			this->gbOrgImg->Dock = System::Windows::Forms::DockStyle::Fill;
			this->gbOrgImg->Location = System::Drawing::Point(0, 0);
			this->gbOrgImg->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->gbOrgImg->Name = L"gbOrgImg";
			this->gbOrgImg->Padding = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->gbOrgImg->Size = System::Drawing::Size(405, 340);
			this->gbOrgImg->TabIndex = 0;
			this->gbOrgImg->TabStop = false;
			this->gbOrgImg->Text = L"vorher";
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
			this->splitConImages->Size = System::Drawing::Size(806, 340);
			this->splitConImages->SplitterDistance = 405;
			this->splitConImages->SplitterWidth = 3;
			this->splitConImages->TabIndex = 21;
			// 
			// btOK
			// 
			this->btOK->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btOK->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->btOK->Location = System::Drawing::Point(722, 562);
			this->btOK->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->btOK->Name = L"btOK";
			this->btOK->Size = System::Drawing::Size(96, 25);
			this->btOK->TabIndex = 19;
			this->btOK->Text = L"OK";
			this->btOK->UseVisualStyleBackColor = true;
			this->btOK->Click += gcnew System::EventHandler(this, &BrightnessContrastForm::btOK_Click);
			// 
			// gbContrast
			// 
			this->gbContrast->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->gbContrast->Controls->Add(this->tboxContrastVal);
			this->gbContrast->Controls->Add(this->tbContrastSlider);
			this->gbContrast->Location = System::Drawing::Point(14, 368);
			this->gbContrast->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->gbContrast->Name = L"gbContrast";
			this->gbContrast->Padding = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->gbContrast->Size = System::Drawing::Size(805, 82);
			this->gbContrast->TabIndex = 23;
			this->gbContrast->TabStop = false;
			this->gbContrast->Text = L"Kontrast";
			// 
			// tboxContrastVal
			// 
			this->tboxContrastVal->Location = System::Drawing::Point(8, 23);
			this->tboxContrastVal->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->tboxContrastVal->Name = L"tboxContrastVal";
			this->tboxContrastVal->ReadOnly = true;
			this->tboxContrastVal->Size = System::Drawing::Size(76, 20);
			this->tboxContrastVal->TabIndex = 1;
			// 
			// tbContrastSlider
			// 
			this->tbContrastSlider->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->tbContrastSlider->Location = System::Drawing::Point(100, 32);
			this->tbContrastSlider->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->tbContrastSlider->Maximum = 50;
			this->tbContrastSlider->Minimum = 1;
			this->tbContrastSlider->Name = L"tbContrastSlider";
			this->tbContrastSlider->Size = System::Drawing::Size(689, 42);
			this->tbContrastSlider->TabIndex = 0;
			this->tbContrastSlider->Value = 1;
			this->tbContrastSlider->Scroll += gcnew System::EventHandler(this, &BrightnessContrastForm::tbContrastSlider_Scroll);
			// 
			// btApplyContrast
			// 
			this->btApplyContrast->Location = System::Drawing::Point(16, 562);
			this->btApplyContrast->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->btApplyContrast->Name = L"btApplyContrast";
			this->btApplyContrast->Size = System::Drawing::Size(94, 24);
			this->btApplyContrast->TabIndex = 24;
			this->btApplyContrast->Text = L"Anwenden";
			this->btApplyContrast->UseVisualStyleBackColor = true;
			this->btApplyContrast->Click += gcnew System::EventHandler(this, &BrightnessContrastForm::btApply_Click);
			// 
			// BrightnessContrastForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(835, 600);
			this->Controls->Add(this->btApplyContrast);
			this->Controls->Add(this->gbContrast);
			this->Controls->Add(this->gbBrigthness);
			this->Controls->Add(this->btCancel);
			this->Controls->Add(this->splitConImages);
			this->Controls->Add(this->btOK);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->Name = L"BrightnessContrastForm";
			this->Text = L"Kontrast und Helligkeit";
			this->Shown += gcnew System::EventHandler(this, &BrightnessContrastForm::BrightnessContrastForm_Shown);
			this->gBOutImg->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pbOutImg))->EndInit();
			this->gbBrigthness->ResumeLayout(false);
			this->gbBrigthness->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tbBrightnessSlider))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pbOrgImg))->EndInit();
			this->gbOrgImg->ResumeLayout(false);
			this->splitConImages->Panel1->ResumeLayout(false);
			this->splitConImages->Panel2->ResumeLayout(false);
			this->splitConImages->ResumeLayout(false);
			this->gbContrast->ResumeLayout(false);
			this->gbContrast->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tbContrastSlider))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

		void tbContrastSlider_Scroll(Object^  sender, EventArgs^  e) {
			changeContrastOfImg();
			btApplyContrast->Enabled = true;
		}

		void BrightnessContrastForm_Shown(Object^  sender, EventArgs^  e) {
			tbContrastSlider->Value = tbContrastSlider->Minimum;
			tbBrightnessSlider->Value = tbBrightnessSlider->Minimum;

			refreshContrast();
			refreshBrightness();
			pbOutImg->Image = nullptr;
			if( mInImg ){
				pbOrgImg->Image = mInImg;
			}else{
				pbOrgImg->Image = nullptr;				
				MessageBox::Show( "Kein Bild geladen","Fehler Eingangsbild",
					MessageBoxButtons::OK, MessageBoxIcon::Stop);
				Close();
			}
			btApplyContrast->Enabled = false;
		}

		void tbBrightnessSlider_Scroll(Object^  sender, EventArgs^  e) {
			changeBrightnessOfImg();
			btApplyContrast->Enabled = true;
		}
		void btOK_Click(Object^  sender, System::EventArgs^  e) {
			applyChanges();
		}
		void btCancel_Click(Object^  sender, EventArgs^  e) {
			Close();
		}
		void btApply_Click(Object^  sender, EventArgs^  e) {			
			mInImg = mTmpImg;
			pbOrgImg->Image = mInImg;
			btApplyContrast->Enabled = false;
		}

};
}
