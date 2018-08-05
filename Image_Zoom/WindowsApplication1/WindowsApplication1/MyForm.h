#pragma once

namespace WindowsApplication1
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TextBox^  textBox1;
	protected:



	protected:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(104, 510);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(107, 44);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Open Image";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click_1);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(37, 24);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(533, 467);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(314, 510);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(107, 44);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Zoom";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(447, 522);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 22);
			this->textBox1->TabIndex = 3;
			this->textBox1->Text = L"1";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(625, 576);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		//宣告Bitmap 儲存開啟的圖
		Bitmap^ image1;

		//宣告為一BitmapData型態 表示像素位置
		Imaging::BitmapData ^ ImageData1;

		//宣告圖像區域(設定為欲讀取、欲修正的圖像區域)
		Rectangle rect;

		//宣告一int格式的指標
		IntPtr ptr, ResultPtr;

		//宣告Byte格式的指標
		Byte* p;
		Byte* R;
		Byte* N;
#pragma endregion
	private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {

		//new一個新的openFileDialog1開啟檔案
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
		//設定Filter，用以限定使用者開啟的檔案
		openFileDialog1->Filter = "點陣圖 (*.bmp)| *.bmp| All files (*.*)| *.*";
		//預設檔案名稱為空值
		openFileDialog1->FileName = "";
		//設定跳出選擇視窗的標題名稱
		openFileDialog1->Title = "載入影像";
		//設定Filter選擇模式(依照Filter數，如本例選擇1表示起始出現的為點陣圖，選擇2表示All filts)
	    openFileDialog1->FilterIndex = 1;


		//跳出檔案選擇視窗(ShowDialog)，並且如果使用者點選檔案，並且檔案名稱超過0個字元，則判斷是為True，進入處理程序
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK && openFileDialog1->FileName->Length > 0)
		{
			//將選取的檔案讀取並且存至Image1
			image1 = safe_cast<Bitmap^>(Image::FromFile(openFileDialog1->FileName));
			//設定rect範圍大小
			rect = Rectangle(0, 0, image1->Width, image1->Height);
			//將影像顯示在pictureBox1
			pictureBox1->Image = image1;
		}
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		//影像放大

		//新增一個空間放置放大影像
		Bitmap^ ZoomImage;
		Imaging::BitmapData^ ZoomImageData;
		ZoomImage = gcnew Bitmap(image1->Width, image1->Height);
		ZoomImageData = ZoomImage->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, image1->PixelFormat);
		ImageData1 = image1->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, image1->PixelFormat);

		//指標指向圖像起始位置
		ResultPtr = ZoomImageData->Scan0;
		R = (Byte*)((Void*)ResultPtr);
		ptr = ImageData1->Scan0;
		p = (Byte*)((Void*)ptr);

		//瀏覽所有像素點，取用像素，處理像素區域
		for (int y = 0; y < image1->Height; y++) {
			for (int x = 0; x < image1->Width; x++) {

				//將影像寬度及高度放大1.2倍  +0.5 取整數
				int xx = x / Convert::ToSingle(textBox1->Text);
				int yy = y / Convert::ToSingle(textBox1->Text);

				//算出目前指標與目標像素的差
				int a = (xx - x) + ((yy - y)*image1->Width);

				//指向目標像素
				N = p + a * 3;

				//取出目標像素放入目前像素
				R[0] = N[0];
				R[1] = N[1];
				R[2] = N[2];

				R += 3;
				p += 3;
			}
		}
		image1->UnlockBits(ImageData1);
		ZoomImage->UnlockBits(ZoomImageData);
		pictureBox1->Image = ZoomImage;
	}
};
}