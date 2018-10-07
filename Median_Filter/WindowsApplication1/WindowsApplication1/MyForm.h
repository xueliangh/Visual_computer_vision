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
			this->button1->Location = System::Drawing::Point(128, 673);
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
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(398, 673);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(107, 44);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Median Filter";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(672, 743);
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
	//Median Filter
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

		////暫存圖空間
		Bitmap ^ temp_Image;
		temp_Image = gcnew Bitmap(image1->Width, image1->Height); //生成一張長寬跟image一樣的Bitmap

		Imaging::BitmapData ^ temp_Image_Data;
		temp_Image_Data = temp_Image->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, image1->PixelFormat);
		
		IntPtr ptr, temp_Ptr;
		temp_Ptr = temp_Image_Data->Scan0;  //將int指標指向Image像素資料的最前面位置
		Byte* q = (Byte*)((Void*)temp_Ptr); //設定指標

		////原圖空間
		ImageData1 = image1->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, image1->PixelFormat);
		ptr = ImageData1->Scan0; //將int指標指向Image像素資料的最前面位置
		Byte* p = (Byte*)((Void*)ptr); //設定指標

		//指標陣列
		Byte* r[9]; 

		//儲存像素與位置編號陣列
		int Array[2][9] = { 0 };
		int temp[2];

		//瀏覽所有像素點，取用像素，處理像素區域
		for (int y = 0; y < image1->Height; y++) {
			for (int x = 0; x < image1->Width; x++) {

				//最外圍像素不處理
				if (y > 0 && x > 0 && y < image1->Height - 1 && x < image1->Width - 1)
				{

					int Masksize = 0;
					//尋訪3X3遮罩的九個像素 並將像素值存下來
					for (int i = -1; i <= 1; i++)
					{
						for (int j = -3; j <= 3; j += 3)
						{
							//指標指向目標像素位址
							r[Masksize] = (Byte*)(Void*)p + i * image1->Width * 3 + j;
							//儲存像素
							Array[0][Masksize] = r[Masksize][0] + r[Masksize][1] + r[Masksize][2];
							//儲存像素編號
							Array[1][Masksize] = Masksize;
							Masksize++;
						}
					}

					int min;
					//只排到第五個 因為第五個就是中位數 不用全部排完
					for (int n = 0; n < 5; ++n)
					{
						min = n;
						//使用氣泡排序法
						for (int o = n + 1; o < 9; ++o)
						{
							if (Array[0][o] < Array[0][min])
								min = o;
							
						}
						//temp暫存像素與編號
						temp[0] = Array[0][n];
						temp[1] = Array[1][n];

						//將較小的像素值與編號搬到目前處理到的位置n
						Array[0][n] = Array[0][min];
						Array[1][n] = Array[1][min];

						//將temp放回去 做swap交換
						Array[0][min] = temp[0];
						Array[1][min] = temp[1];
					}

					//找到排序完第5個像素值得指標位址 將位址的B G R放到目前像素
					q[0] = r[Array[1][4]][0];
					q[1] = r[Array[1][4]][1];
					q[2] = r[Array[1][4]][2];
				}
				else
				{
					q[0] = p[0];
					q[1] = p[1];
					q[2] = p[2];
				}
				q += 3;
				p += 3;
			}
		}

		//解鎖像素位置
		image1->UnlockBits(ImageData1);
		temp_Image->UnlockBits(temp_Image_Data);
		//顯示在PictureBox上
		pictureBox1->Image = temp_Image;
	}
};
}