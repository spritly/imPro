/****************************************************************************** 
** @Filename:	MainForm.h
** @Project: 	"Bildbearbeitung"
** @author:		B.Hentzschel 
** @letzte Ae:	2012-10-25
** 
** Haupt-GUI zur Steuerung des BV Prg
******************************************************************************/
#pragma once

#include "IpManager.h"
#include "IpFilter.h"
#include "BinarizeForm.h"
#include "TransparencyForm.h"
#include "BrightnessContrastForm.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;

using namespace IMGProcessing;


namespace ImPro {
	public ref class MainForm : public System::Windows::Forms::Form{

	private:
		IpManager^ mIpManager;
		// verzeichnis beim Laden/Speichern von Bildern:
		static String^ mImgDir = "..\\bilder";
		static String^ mPrgPath;
		BinarizeForm^ mBinarizeForm;
		TransparencyForm^ mTransparencyForm;
		BrightnessContrastForm^ mBrightnessContrastForm;
		enum class ImgKind{ inImg, outImg };
		enum class ImgFormats{ bmp=1, jpg=2 };

		// vom benutzer eingestellter Cursor (mauszeiger)
		System::Windows::Forms::Cursor^ normalCursor;

	public:
		MainForm(void){
			InitializeComponent();
			init();
		}

	protected:
		~MainForm(){
			if (components){
				delete components;
			}
		}

	private: System::Windows::Forms::Button^  btClose;
	private: System::Windows::Forms::Button^  btProcessImg;
	private: System::Windows::Forms::Button^  btLoadImg;
	private: System::Windows::Forms::SplitContainer^  splitConAll;
	private: System::Windows::Forms::TreeView^  tvFilterList;
	private:	System::Windows::Forms::SaveFileDialog^  saveDlg;
	private: System::Windows::Forms::ImageList^  imgListTreeview;
	private: System::Windows::Forms::ToolStripStatusLabel^  lbImpDura;
	private: System::Windows::Forms::SplitContainer^  splitContainer2;
	private: System::Windows::Forms::MenuStrip^  menu;
	private: System::Windows::Forms::StatusStrip^  statusBar;
	private: System::Windows::Forms::ToolStripMenuItem^  menuItemFile;
	private: System::Windows::Forms::ToolStripMenuItem^  menuItemClose;
	private: System::Windows::Forms::ToolStripMenuItem^  menuItemImage;
	private: System::Windows::Forms::ToolStripMenuItem^  menuItemLoadImg;
	private: System::Windows::Forms::ToolStripMenuItem^  menuItemSaveResultImg;
	private: System::Windows::Forms::ToolStripMenuItem^  menuItemInfo;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  menuItemBinarize;
	private: System::Windows::Forms::GroupBox^  gbInImg;
	private: System::Windows::Forms::PictureBox^  pbInImg;
	private: System::Windows::Forms::GroupBox^  gbResultImg;
	private: System::Windows::Forms::PictureBox^  pbResultImg;
	private: System::Windows::Forms::OpenFileDialog^  loadDlg;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::ToolStripMenuItem^  menuItemGreyValImg;
	private: System::Windows::Forms::ToolStripMenuItem^  menuItemTranparency;
	private: System::Windows::Forms::ToolStripMenuItem^  menuItemBrightnessContrast;
	private: System::Windows::Forms::ContextMenuStrip^  cMenuResImg;
	private: System::Windows::Forms::ToolStripMenuItem^  alsEingangsbildSetzenToolStripMenuItem;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void){
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->btClose = (gcnew System::Windows::Forms::Button());
			this->btProcessImg = (gcnew System::Windows::Forms::Button());
			this->btLoadImg = (gcnew System::Windows::Forms::Button());
			this->splitConAll = (gcnew System::Windows::Forms::SplitContainer());
			this->tvFilterList = (gcnew System::Windows::Forms::TreeView());
			this->splitContainer2 = (gcnew System::Windows::Forms::SplitContainer());
			this->gbInImg = (gcnew System::Windows::Forms::GroupBox());
			this->pbInImg = (gcnew System::Windows::Forms::PictureBox());
			this->gbResultImg = (gcnew System::Windows::Forms::GroupBox());
			this->pbResultImg = (gcnew System::Windows::Forms::PictureBox());
			this->cMenuResImg = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->alsEingangsbildSetzenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->imgListTreeview = (gcnew System::Windows::Forms::ImageList(this->components));
			this->menu = (gcnew System::Windows::Forms::MenuStrip());
			this->menuItemFile = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuItemClose = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuItemImage = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuItemLoadImg = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuItemSaveResultImg = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->menuItemGreyValImg = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuItemBinarize = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuItemTranparency = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuItemBrightnessContrast = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuItemInfo = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->statusBar = (gcnew System::Windows::Forms::StatusStrip());
			this->lbImpDura = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->loadDlg = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveDlg = (gcnew System::Windows::Forms::SaveFileDialog());
			this->splitConAll->Panel1->SuspendLayout();
			this->splitConAll->Panel2->SuspendLayout();
			this->splitConAll->SuspendLayout();
			this->splitContainer2->Panel1->SuspendLayout();
			this->splitContainer2->Panel2->SuspendLayout();
			this->splitContainer2->SuspendLayout();
			this->gbInImg->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pbInImg))->BeginInit();
			this->gbResultImg->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pbResultImg))->BeginInit();
			this->cMenuResImg->SuspendLayout();
			this->menu->SuspendLayout();
			this->statusBar->SuspendLayout();
			this->SuspendLayout();
			// 
			// btClose
			// 
			this->btClose->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btClose->Location = System::Drawing::Point(657, 358);
			this->btClose->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->btClose->Name = L"btClose";
			this->btClose->Size = System::Drawing::Size(68, 25);
			this->btClose->TabIndex = 1;
			this->btClose->Text = L"Beenden";
			this->btClose->UseVisualStyleBackColor = true;
			this->btClose->Click += gcnew System::EventHandler(this, &MainForm::btClose_Click);
			// 
			// btProcessImg
			// 
			this->btProcessImg->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->btProcessImg->Location = System::Drawing::Point(249, 358);
			this->btProcessImg->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->btProcessImg->Name = L"btProcessImg";
			this->btProcessImg->Size = System::Drawing::Size(96, 25);
			this->btProcessImg->TabIndex = 2;
			this->btProcessImg->Text = L"Bildverarbeitung";
			this->btProcessImg->UseVisualStyleBackColor = true;
			this->btProcessImg->Click += gcnew System::EventHandler(this, &MainForm::btProcessImg_Click);
			// 
			// btLoadImg
			// 
			this->btLoadImg->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->btLoadImg->Location = System::Drawing::Point(140, 358);
			this->btLoadImg->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->btLoadImg->Name = L"btLoadImg";
			this->btLoadImg->Size = System::Drawing::Size(96, 25);
			this->btLoadImg->TabIndex = 3;
			this->btLoadImg->Text = L"Bild laden";
			this->btLoadImg->UseVisualStyleBackColor = true;
			this->btLoadImg->Click += gcnew System::EventHandler(this, &MainForm::btLoadImg_Click);
			// 
			// splitConAll
			// 
			this->splitConAll->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->splitConAll->Location = System::Drawing::Point(9, 29);
			this->splitConAll->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->splitConAll->Name = L"splitConAll";
			// 
			// splitConAll.Panel1
			// 
			this->splitConAll->Panel1->Controls->Add(this->tvFilterList);
			// 
			// splitConAll.Panel2
			// 
			this->splitConAll->Panel2->Controls->Add(this->splitContainer2);
			this->splitConAll->Size = System::Drawing::Size(716, 316);
			this->splitConAll->SplitterDistance = 125;
			this->splitConAll->SplitterWidth = 3;
			this->splitConAll->TabIndex = 4;
			// 
			// tvFilterList
			// 
			this->tvFilterList->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tvFilterList->Location = System::Drawing::Point(0, 0);
			this->tvFilterList->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->tvFilterList->Name = L"tvFilterList";
			this->tvFilterList->Size = System::Drawing::Size(125, 316);
			this->tvFilterList->TabIndex = 10;
			this->tvFilterList->NodeMouseClick += gcnew System::Windows::Forms::TreeNodeMouseClickEventHandler(this, &MainForm::tvFilterList_NodeMouseClick);
			// 
			// splitContainer2
			// 
			this->splitContainer2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer2->Location = System::Drawing::Point(0, 0);
			this->splitContainer2->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->splitContainer2->Name = L"splitContainer2";
			// 
			// splitContainer2.Panel1
			// 
			this->splitContainer2->Panel1->Controls->Add(this->gbInImg);
			// 
			// splitContainer2.Panel2
			// 
			this->splitContainer2->Panel2->Controls->Add(this->gbResultImg);
			this->splitContainer2->Size = System::Drawing::Size(588, 316);
			this->splitContainer2->SplitterDistance = 292;
			this->splitContainer2->SplitterWidth = 3;
			this->splitContainer2->TabIndex = 0;
			// 
			// gbInImg
			// 
			this->gbInImg->Controls->Add(this->pbInImg);
			this->gbInImg->Dock = System::Windows::Forms::DockStyle::Fill;
			this->gbInImg->Location = System::Drawing::Point(0, 0);
			this->gbInImg->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->gbInImg->Name = L"gbInImg";
			this->gbInImg->Padding = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->gbInImg->Size = System::Drawing::Size(292, 316);
			this->gbInImg->TabIndex = 0;
			this->gbInImg->TabStop = false;
			this->gbInImg->Text = L"Eingangsbild";
			// 
			// pbInImg
			// 
			this->pbInImg->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pbInImg->Location = System::Drawing::Point(2, 15);
			this->pbInImg->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->pbInImg->Name = L"pbInImg";
			this->pbInImg->Size = System::Drawing::Size(288, 299);
			this->pbInImg->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pbInImg->TabIndex = 0;
			this->pbInImg->TabStop = false;
			// 
			// gbResultImg
			// 
			this->gbResultImg->Controls->Add(this->pbResultImg);
			this->gbResultImg->Dock = System::Windows::Forms::DockStyle::Fill;
			this->gbResultImg->Location = System::Drawing::Point(0, 0);
			this->gbResultImg->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->gbResultImg->Name = L"gbResultImg";
			this->gbResultImg->Padding = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->gbResultImg->Size = System::Drawing::Size(293, 316);
			this->gbResultImg->TabIndex = 0;
			this->gbResultImg->TabStop = false;
			this->gbResultImg->Text = L"Ergebnisbild";
			// 
			// pbResultImg
			// 
			this->pbResultImg->ContextMenuStrip = this->cMenuResImg;
			this->pbResultImg->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pbResultImg->Location = System::Drawing::Point(2, 15);
			this->pbResultImg->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->pbResultImg->Name = L"pbResultImg";
			this->pbResultImg->Size = System::Drawing::Size(289, 299);
			this->pbResultImg->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pbResultImg->TabIndex = 0;
			this->pbResultImg->TabStop = false;
			// 
			// cMenuResImg
			// 
			this->cMenuResImg->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->alsEingangsbildSetzenToolStripMenuItem});
			this->cMenuResImg->Name = L"cMenuResImg";
			this->cMenuResImg->Size = System::Drawing::Size(199, 26);
			// 
			// alsEingangsbildSetzenToolStripMenuItem
			// 
			this->alsEingangsbildSetzenToolStripMenuItem->Name = L"alsEingangsbildSetzenToolStripMenuItem";
			this->alsEingangsbildSetzenToolStripMenuItem->Size = System::Drawing::Size(198, 22);
			this->alsEingangsbildSetzenToolStripMenuItem->Text = L"als Eingangsbild  setzen";
			this->alsEingangsbildSetzenToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::alsEingangsbildSetzenToolStripMenuItem_Click);
			// 
			// imgListTreeview
			// 
			this->imgListTreeview->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"imgListTreeview.ImageStream")));
			this->imgListTreeview->TransparentColor = System::Drawing::Color::Transparent;
			this->imgListTreeview->Images->SetKeyName(0, L"folder_selected.jpg");
			this->imgListTreeview->Images->SetKeyName(1, L"filterImage.jpg");
			// 
			// menu
			// 
			this->menu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->menuItemFile, this->menuItemImage, 
				this->menuItemInfo});
			this->menu->Location = System::Drawing::Point(0, 0);
			this->menu->Name = L"menu";
			this->menu->Padding = System::Windows::Forms::Padding(4, 2, 0, 2);
			this->menu->Size = System::Drawing::Size(734, 24);
			this->menu->TabIndex = 5;
			this->menu->Text = L"menu";
			// 
			// menuItemFile
			// 
			this->menuItemFile->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->menuItemClose});
			this->menuItemFile->Name = L"menuItemFile";
			this->menuItemFile->Size = System::Drawing::Size(44, 20);
			this->menuItemFile->Text = L"&Datei";
			// 
			// menuItemClose
			// 
			this->menuItemClose->Name = L"menuItemClose";
			this->menuItemClose->Size = System::Drawing::Size(127, 22);
			this->menuItemClose->Text = L"&Beenden";
			this->menuItemClose->Click += gcnew System::EventHandler(this, &MainForm::menuItemClose_Click);
			// 
			// menuItemImage
			// 
			this->menuItemImage->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {this->menuItemLoadImg, 
				this->menuItemSaveResultImg, this->toolStripSeparator1, this->menuItemGreyValImg, this->menuItemBinarize, this->menuItemTranparency, 
				this->menuItemBrightnessContrast});
			this->menuItemImage->Name = L"menuItemImage";
			this->menuItemImage->Size = System::Drawing::Size(35, 20);
			this->menuItemImage->Text = L"B&ild";
			// 
			// menuItemLoadImg
			// 
			this->menuItemLoadImg->Name = L"menuItemLoadImg";
			this->menuItemLoadImg->Size = System::Drawing::Size(191, 22);
			this->menuItemLoadImg->Text = L"&Laden";
			this->menuItemLoadImg->Click += gcnew System::EventHandler(this, &MainForm::menuItemLoadImg_Click);
			// 
			// menuItemSaveResultImg
			// 
			this->menuItemSaveResultImg->Name = L"menuItemSaveResultImg";
			this->menuItemSaveResultImg->Size = System::Drawing::Size(191, 22);
			this->menuItemSaveResultImg->Text = L"Ergebnisbild &speichern";
			this->menuItemSaveResultImg->Click += gcnew System::EventHandler(this, &MainForm::menuItemSaveResultImg_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(188, 6);
			// 
			// menuItemGreyValImg
			// 
			this->menuItemGreyValImg->Name = L"menuItemGreyValImg";
			this->menuItemGreyValImg->Size = System::Drawing::Size(191, 22);
			this->menuItemGreyValImg->Text = L"Grauwertbild";
			this->menuItemGreyValImg->Click += gcnew System::EventHandler(this, &MainForm::menueItemGreyValImg_Click);
			// 
			// menuItemBinarize
			// 
			this->menuItemBinarize->Name = L"menuItemBinarize";
			this->menuItemBinarize->Size = System::Drawing::Size(191, 22);
			this->menuItemBinarize->Text = L"Bin&arisierung";
			this->menuItemBinarize->Click += gcnew System::EventHandler(this, &MainForm::menuItemBinarize_Click);
			// 
			// menuItemTranparency
			// 
			this->menuItemTranparency->Name = L"menuItemTranparency";
			this->menuItemTranparency->Size = System::Drawing::Size(191, 22);
			this->menuItemTranparency->Text = L"Transparenz";
			this->menuItemTranparency->Click += gcnew System::EventHandler(this, &MainForm::menuItemTranparency_Click);
			// 
			// menuItemBrightnessContrast
			// 
			this->menuItemBrightnessContrast->Name = L"menuItemBrightnessContrast";
			this->menuItemBrightnessContrast->Size = System::Drawing::Size(191, 22);
			this->menuItemBrightnessContrast->Text = L"Helligkeit / Kontrast";
			this->menuItemBrightnessContrast->Click += gcnew System::EventHandler(this, &MainForm::menuItemBrightnessContrast_Click);
			// 
			// menuItemInfo
			// 
			this->menuItemInfo->Name = L"menuItemInfo";
			this->menuItemInfo->Size = System::Drawing::Size(39, 20);
			this->menuItemInfo->Text = L"&Info";
			// 
			// statusBar
			// 
			this->statusBar->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->lbImpDura});
			this->statusBar->Location = System::Drawing::Point(0, 392);
			this->statusBar->Name = L"statusBar";
			this->statusBar->Padding = System::Windows::Forms::Padding(1, 0, 10, 0);
			this->statusBar->Size = System::Drawing::Size(734, 22);
			this->statusBar->TabIndex = 6;
			this->statusBar->Text = L"statusBar";
			// 
			// lbImpDura
			// 
			this->lbImpDura->Name = L"lbImpDura";
			this->lbImpDura->Size = System::Drawing::Size(0, 17);
			// 
			// loadDlg
			// 
			this->loadDlg->FileName = L"loadImgDialog";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(734, 414);
			this->Controls->Add(this->statusBar);
			this->Controls->Add(this->splitConAll);
			this->Controls->Add(this->btLoadImg);
			this->Controls->Add(this->btProcessImg);
			this->Controls->Add(this->btClose);
			this->Controls->Add(this->menu);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menu;
			this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->Name = L"MainForm";
			this->Text = L"ImPro - Image Processing";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->splitConAll->Panel1->ResumeLayout(false);
			this->splitConAll->Panel2->ResumeLayout(false);
			this->splitConAll->ResumeLayout(false);
			this->splitContainer2->Panel1->ResumeLayout(false);
			this->splitContainer2->Panel2->ResumeLayout(false);
			this->splitContainer2->ResumeLayout(false);
			this->gbInImg->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pbInImg))->EndInit();
			this->gbResultImg->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pbResultImg))->EndInit();
			this->cMenuResImg->ResumeLayout(false);
			this->menu->ResumeLayout(false);
			this->menu->PerformLayout();
			this->statusBar->ResumeLayout(false);
			this->statusBar->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	private:	
		void init(){
			mIpManager = gcnew IpManager();
			mPrgPath = Path::GetFullPath(Directory::GetCurrentDirectory());
			String^ imgFilter = "BITMAP (*.bmp)|*.bmp|"+ "JPEG (*.jpg)|*.jpg";
			String^ imgPath =	Path::Combine( mPrgPath, mImgDir );
			// loadDialog:
			loadDlg->InitialDirectory = imgPath;
			loadDlg->Filter = imgFilter;
			loadDlg->FileName = String::Empty;
			// saveDialog
			saveDlg->InitialDirectory = imgPath;
			saveDlg->Filter = imgFilter;
			saveDlg->FileName = String::Empty;

			// dialoge zum Bearbeiten eines Bildes:
			mBinarizeForm = gcnew BinarizeForm();	
			mTransparencyForm = gcnew TransparencyForm();
			mBrightnessContrastForm = gcnew BrightnessContrastForm();

			// fuer Anzeige der Eieruhr als Wartezeit
			normalCursor = System::Windows::Forms::Cursor::Current;
		}

		void showWaitCursor(){
			System::Windows::Forms::Cursor::Current = Cursors::WaitCursor;
		}

		void resetWaitCursor(){
			System::Windows::Forms::Cursor::Current = normalCursor;
		}

		bool loadImage(){
			pbResultImg->Image = nullptr;
			pbInImg->Image = nullptr;
			ShowDurationOfImp( nullptr );
			if( loadDlg->ShowDialog() == Windows::Forms::DialogResult::OK){ 
				showWaitCursor();
				mIpManager->InImg = gcnew Bitmap(loadDlg->FileName);
				resetWaitCursor();
			}else{
				return false;
			}
			showImage( ImgKind::inImg );
			return true;
		}

		bool saveImage( Bitmap^ aImg ){
			if( aImg != nullptr && saveDlg->ShowDialog() == Windows::Forms::DialogResult::OK){
				try{
					if( saveDlg->FilterIndex == 1 )										
						aImg->Save( saveDlg->FileName, Imaging::ImageFormat::Bmp	 );
					else
						aImg->Save( saveDlg->FileName, Imaging::ImageFormat::Jpeg);
				}catch( Exception^ ex ){
					System::Diagnostics::Debug::WriteLine( ex->ToString() );
				}
				return true;
			}
			return false;
		}

		void showImage( ImgKind aKindOfImg ){	
			if( aKindOfImg == ImgKind::inImg ) {
				pbInImg->Image = mIpManager->InImg;
				pbResultImg->Image = nullptr;
			}else{
				pbResultImg->Image = mIpManager->OutImg;			
			}
		}

		void ShowDurationOfImp( TimeSpan^ ts ){
			if( ts )
				lbImpDura->Text = "Dauer = " + ts->TotalSeconds.ToString("F4") + " s";
			else
				lbImpDura->Text = String::Empty;
		}
		
		// schaut nach, ob eine FilterKategorie schon im Treeview vorh ist
		// und wenn ja liefert die entspr. Node, an der die Kategorie haengt, zurueck
		TreeNode^ findCategoryNodeInTreeview( String^ aCategoryName ){
			TreeNode^ node = nullptr;
			for( int i = 0; i < tvFilterList->Nodes->Count; i++ ){
				if( tvFilterList->Nodes[i]->Name == aCategoryName )
					return tvFilterList->Nodes[i];
			}
			return nullptr;
		}
		
		// erzeugt im Treeview eine neues Filterkategorie als Node
		TreeNode^ createCategoryNode( String^ aCategoryName ){
			TreeNode^ node = gcnew TreeNode();
			node->Name = aCategoryName;
			node->Text = aCategoryName;
			node->Tag  = nullptr;			
			node->ImageIndex = 0;
			tvFilterList->Nodes->Add( node );
			return node;
		}
		
		// zeigt alle zur Verfuegung stehenden Filter im Treeview an
		void fillTreeviewWithAvailableFilter(){
			tvFilterList->BeginUpdate();

			tvFilterList->Nodes->Clear();
			tvFilterList->ImageList = imgListTreeview;
			for( vector<IpFilter*>::iterator iter = mIpManager->pAvailableFilterList->begin();
					iter != mIpManager->pAvailableFilterList->end(); iter++)
			{
				String^ filterName = (*iter)->mName.ToString();
				String^ categoryNameOfFilter = (*iter)->mCategory.ToString();

				//1. schaue im Treeview nach, ob dieser name bei 1Level-Node schon existiert
				TreeNode^ categoryNode = findCategoryNodeInTreeview( categoryNameOfFilter );
				if( categoryNode == nullptr ){
					// kategoryName existiert noch nicht, also anlegen
					categoryNode = createCategoryNode( categoryNameOfFilter );
				}

				//2. ordne den Filter in der kategorieNode ein als unterknoten
				TreeNode^ node = gcnew TreeNode();
				node->Name	= categoryNameOfFilter;
				node->Text	= filterName; 
				node->Tag	= (*iter)->mName;	
				// node->tag = (*iter);
				// problem:unmanaged Klasse ist kein managed Object, kann also
				// nciht an NodeTag gehangen werden
				// deshalb, entweder Wrapper um managed Filter
				// oder nix am Tag, dafür aber Filter nach Name erzeugen
				node->ImageIndex = 1;				
				categoryNode->Nodes->Add( node );

				tvFilterList->EndUpdate();
			}
		}
	 
		// der im Treeview ausgewaehlte Filter wird auf das Eingangsbild angewandt
		void processImage(){
			bool isError = false;
			// auslesen des markierten Filters im Treeview
			if( tvFilterList->SelectedNode == nullptr){
				// kein Filter gewaehlt
				MessageBox::Show(
					"Bitte wählen Sie einen Filter aus.",
					"Filterauswahl",
					MessageBoxButtons::OK, 
					MessageBoxIcon::Error);
				return;
			}

			FilterName currFilterName = (FilterName) tvFilterList->SelectedNode->Tag;
			IpFilter* currFilter = mIpManager->GetFilterByName( currFilterName );
			if( currFilter != NULL){
				// achtung speicherverwaltung, da filter unmanaged
				delete mIpManager->CurrFilter;
				mIpManager->CurrFilter = currFilter;

				// ********* Start BV-Zeitmessung
				System::Diagnostics::Stopwatch^ stopWatch = 
							gcnew System::Diagnostics::Stopwatch();
				stopWatch->Start();
				// CursorArt aendern, damit man sieht, das Bild bearbeitet wird:
				System::Windows::Forms::Cursor::Current = Cursors::WaitCursor;				
				// *********

				if( !mIpManager->ProcessImage() ){
					MessageBox::Show(
							"Fehler bei der Bildverarbeitung",
							"Fehlermeldung",
							MessageBoxButtons::OK, 
							MessageBoxIcon::Error);
					isError = true;
				}

				//********** Ende BV-Zeitmessung
				ShowDurationOfImp( stopWatch->Elapsed );
				stopWatch->Stop();
				System::Windows::Forms::Cursor::Current = normalCursor;
				//**********
				
				if( isError )
					pbResultImg->Image = nullptr;

				// ergbild anzeigen:
				showImage( ImgKind::outImg );
			}
		}

		void showBinarizeForm(){
			mBinarizeForm->mIpManager = this->mIpManager; 
			if( mBinarizeForm->ShowDialog() == Windows::Forms::DialogResult::OK ){
				delete this->mIpManager->OutImg;
				this->mIpManager->OutImg = mBinarizeForm->BinImg;
				showImage( ImgKind::outImg );
			}
		}

		void showTransparencyForm(){
			mTransparencyForm->InImg = mIpManager->InImg;
			if( mTransparencyForm->ShowDialog() == Windows::Forms::DialogResult::OK ){
				delete this->mIpManager->OutImg;
				this->mIpManager->OutImg = mTransparencyForm->OutImg;
				showImage( ImgKind::outImg );
			}
		}

		void showBrightnessContrastForm(){
			mBrightnessContrastForm->InImg = mIpManager->InImg;
			if( mBrightnessContrastForm->ShowDialog() == Windows::Forms::DialogResult::OK ){
				delete this->mIpManager->OutImg;
				this->mIpManager->OutImg = mBrightnessContrastForm->OutImg;
				showImage( ImgKind::outImg );
			}
		}

		// Grauwertbild vom Eingangsbild erzeugen
		void setInImgToGreyValImg(){
			if( !mIpManager->InImg ){
				// kein Bild geladen
				MessageBox::Show(
					"Bitte laden Sie ein Bild.",
					"Bildauswahl Fehler",
					MessageBoxButtons::OK, 
					MessageBoxIcon::Error);
				return;			
			}
			bool isError = false;
			try{
				IpImage* gwImgBitmap = mIpManager->GetGreyScaleImg( mIpManager->InIpImage ); 
				mIpManager->OutImg = gwImgBitmap->PixImgToBitmap();
				delete gwImgBitmap;
			}catch( Exception^ ex){
				MessageBox::Show(
					"Fehler beim Erzeugen des Grauwert Bildes",
					"GrauwertBild",
					MessageBoxButtons::OK, 
					MessageBoxIcon::Error);
				isError = true;
			}

			if( isError )
				pbResultImg->Image = nullptr;

			showImage( ImgKind::outImg );
		}

		void setOutImgAsInImg(){
			mIpManager->InImg = mIpManager->OutImg;
			pbResultImg->Image = nullptr;
			pbInImg->Image = mIpManager->InImg;
		}

		void btClose_Click(Object^  sender, EventArgs^  e) {
			Close();
		}

		void btLoadImg_Click(Object^  sender, EventArgs^  e) {
			loadImage();
		}

		void btProcessImg_Click(System::Object^  sender, System::EventArgs^  e) {
			pbResultImg->Image = nullptr;
			processImage();
		}

		void MainForm_Load(Object^  sender, EventArgs^  e) {
			fillTreeviewWithAvailableFilter();
		}

		void menuItemSaveResultImg_Click(Object^  sender, EventArgs^  e) {
			if( !saveImage( mIpManager->OutImg ) ){
				MessageBox::Show( "Fehler beim Speichern des Ergebnis Bildes!",
					"Fehler beim Speichern", MessageBoxButtons::OK,
					MessageBoxIcon::Error);
			}
		}

		void menuItemLoadImg_Click(Object^  sender, EventArgs^  e) {
			if( !loadImage()){
				MessageBox::Show( "Fehler beim Laden des Bildes!",
					"Fehler beim Laden", MessageBoxButtons::OK,
					MessageBoxIcon::Error);
			}
		}
		void menuItemClose_Click(Object^  sender, EventArgs^  e) {
			Close();
		}
		void tvFilterList_NodeMouseClick(Object^  sender, TreeNodeMouseClickEventArgs^  e) {
			ShowDurationOfImp( nullptr );			
		}

		void menuItemBinarize_Click(System::Object^  sender, System::EventArgs^  e) {
			showBinarizeForm();	
		}

		void menueItemGreyValImg_Click(Object^  sender, EventArgs^  e) {
			setInImgToGreyValImg();
		}
		void menuItemTranparency_Click(Object^  sender, EventArgs^  e) {
			showTransparencyForm();
		}
		void menuItemBrightnessContrast_Click(Object^  sender, EventArgs^  e) {
			showBrightnessContrastForm();
		}
		void alsEingangsbildSetzenToolStripMenuItem_Click(Object^  sender, EventArgs^  e) {
			setOutImgAsInImg();
		}
};
}
