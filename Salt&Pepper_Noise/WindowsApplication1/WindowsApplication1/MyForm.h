#pragma once
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <iostream>

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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(235, 510);
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
			this->pictureBox1->Size = System::Drawing::Size(533, 464);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(379, 510);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(107, 44);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Noise";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(625, 576);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

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
		//影像增加椒鹽雜訊

		//宣告NoiseImage為BitMap^型態
		Bitmap^ NoiseImage;

		NoiseImage = gcnew Bitmap(image1->Width, image1->Height);
		//宣告NoiseImageData為BitmapData^型態，表示像素資料位置
		Imaging::BitmapData^ NoiseImageData;
		//鎖定欲處理像素位置
		NoiseImageData = NoiseImage->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, image1->PixelFormat);
		//將int指標指向Image像素資料的最前面位置
		ResultPtr = NoiseImageData->Scan0;
		//設定指標
		R = (Byte*)((Void*)ResultPtr);

		//鎖定原圖欲處理像素位置
		ImageData1 = image1->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, image1->PixelFormat);
		//將int指標指向原圖像素資料最前面位置
		ptr = ImageData1->Scan0;
		//設定指標
		p = (Byte*)((Void*)ptr);

		double mean = 0;//期望值
		double std = 1;//標準差
		double u, v;//均勻分布數值
		double X;//常態分佈數值

		//瀏覽所有像素點，取用像素，處理像素區域
		for (int y = 0; y < image1->Height; y++)
		{
			for (int x = 0; x < image1->Width; x++)
			{
				u = rand() / (double)RAND_MAX;//RAND_MAX=32767
				v = rand() / (double)RAND_MAX;

				X = sqrt(-2.0 * log(u)) * cos(2.0 * M_PI * v) * std + mean;//M_PI=3.14159

				if (X > 2 || X < -2) 
				{
					if (X > 2) //撒鹽
					{
						R[0] = 255;
						R[1] = 255;
						R[2] = 255;
					}
					else if (X < -2)  //撒黑胡椒
					{
						R[0] = 0;
						R[1] = 0;
						R[2] = 0;
					}
				}
				else
				{
					//拷貝原圖像素
					R[0] = p[0];
					R[1] = p[1];
					R[2] = p[2];
				}

				R += 3;
				p += 3;
			}
		}

		//解鎖像素位置
		image1->UnlockBits(ImageData1);
		NoiseImage->UnlockBits(NoiseImageData);
		//顯示在PictureBox上
		pictureBox1->Image = NoiseImage;
	}
};
}