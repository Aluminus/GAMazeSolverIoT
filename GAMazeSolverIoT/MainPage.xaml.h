//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "GARunner.h"
#include "MainPage.g.h"
#include <ppl.h>
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Shapes;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Media;
using namespace Windows::System::Threading;

namespace GAMazeSolver
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();
		void CellClick(Object^ sender, PointerRoutedEventArgs^ e);
		void InitializeMazeGrid(Grid^ grid, bool canClick);
		void RefreshCell(int x, int y, int s, bool source);
		

	private: 
		GARunner runner;
		void btnStep_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void btnPrev_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void btnNext_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void RefreshMaze(bool source);
		void btnRun_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void RefreshMazeTick(Object^ sender, Object^ eventArgs);
		DispatcherTimer^ runnerTimer;
		void btnStop_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void MazeBrowse_PointerWheelChanged(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void LoadFileAndInitialize();
		bool isStopped;
	};
}
