#include "MyForm.h"
#include <iostream>

using namespace WindowsApplication1;

[STAThreadAttribute]

int main(void)
{
	//true == 1, false == 0
	// 建立任何控制項之前，先啟用 Windows XP 視覺化效果
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// 建立主視窗並執行
	Application::Run(gcnew MyForm());

	//結束程式執行，並回傳 0 代表程式執行正常無異狀。
	return 0;
}