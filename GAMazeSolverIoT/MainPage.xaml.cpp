//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "MazeCellWrapper.h"

using namespace GAMazeSolver;



// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

MainPage::MainPage()
	:runner(1000, 500), isStopped(true)
{
	InitializeComponent();

	InitializeMazeGrid(MazeSource, true);
	InitializeMazeGrid(MazeBrowse, false);
	LoadFileAndInitialize();
	RefreshMaze(true);
	RefreshMaze(false);
}

void MainPage::LoadFileAndInitialize()
{
	Windows::Storage::StorageFolder^ _Folder = Windows::ApplicationModel::Package::Current->InstalledLocation;
	try
	{
		// acquire file
		auto _FileContinuation = concurrency::create_task(Windows::Storage::StorageFile::GetFileFromApplicationUriAsync(ref new Uri("ms-appx:///Assets/test_maze.txt"))).then(
			[this](Windows::Storage::StorageFile^ f2)
		{
			// read content
			auto _ReadContinuation = concurrency::create_task(Windows::Storage::FileIO::ReadTextAsync(f2)).then(
				[this](String^ s)
			{
				runner.LoadString(s->Data());
				runner.InitializeSolvers();
				RefreshMaze(true);
				RefreshMaze(false);
				txtSolverCursor->Text = runner.gaCursor + "/" + (runner.gaList.size() - 1);
				chkSolved->IsChecked = runner.gaList[runner.gaCursor].isSolved();
				txtSteps->Text = "Steps: " + runner.gaList[runner.gaCursor].Steps();
			});
		});
	}
	catch (const std::exception&)
	{
		// Couldn't find the file, keep going I guess...
	}
}

void MainPage::InitializeMazeGrid(Grid^ grid, bool canClick)
{
	for (int y = 0; y < MazeCell::MAZESIZE; y++)
	{
		for (int x = 0; x < MazeCell::MAZESIZE; x++)
		{
			auto r = ref new Rectangle();
			auto g = ref new MazeCellWrapper();
			r->Tag = g;	// We assign the maze cell to the tag so we can recover it later
			r->Stroke = ref new SolidColorBrush(Windows::UI::Colors::Black);
			r->StrokeThickness = 0.5;
			r->Fill = ref new SolidColorBrush{ g->CellBrush() };
			r->Height = 25;
			r->Width = 25;
			if (canClick)
				r->PointerReleased += ref new PointerEventHandler(this, &MainPage::CellClick);
			grid->SetRow(r, y);
			g->SetRow(y);
			grid->SetColumn(r, x);
			g->SetColumn(x);
			grid->Children->Append(r);
		}
	}
}

void MainPage::RefreshCell(int x, int y, int s, bool source)
{
	Rectangle^ getRekt;
	if (source)
		getRekt = (Rectangle^)MazeSource->Children->GetAt(y * MazeCell::MAZESIZE + x);
	else
		getRekt = (Rectangle^)MazeBrowse->Children->GetAt(y * MazeCell::MAZESIZE + x);
	auto g = ((MazeCellWrapper^)getRekt->Tag);
	g->SetCellStatus((int)s);
	getRekt->Fill = ref new SolidColorBrush(g->CellBrush());
}

void MainPage::CellClick(Object^ sender, PointerRoutedEventArgs^ e)
{
	if (runnerTimer != nullptr && runnerTimer->IsEnabled)
		return;	// We don't want to interrupt the solvers if they are running
	Rectangle^ x = (Rectangle^)sender;
	MazeCellWrapper^ c = (MazeCellWrapper^)x->Tag;
	c->SetCellStatus(c->GetCellStatus() + (int)MazeCell::CELLSTATE::Wall);	// Increment color
	if (c->GetCellStatus() > (int)MazeCell::CELLSTATE::Valid)	// Color overflows to Free
		c->SetCellStatus((int)MazeCell::CELLSTATE::Free);
	runner.sourceMaze[c->GetColumn()][c->GetRow()] = (MazeCell::CELLSTATE)c->GetCellStatus();
	runner.UpdateWalls();	// If we added walls, the solvers need to know
	x->Fill = ref new SolidColorBrush(c->CellBrush());
}

void MainPage::btnStep_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	runner.ShouldRunCallback = []() {return true; };
	runner.RunEpoch();	// Honestly, we shouldn't be doing this work on the UI thread, but it's only one epoch...
	txtEpoch->Text = "Epoch: " + runner.epochs;
	txtSteps->Text = "Steps: " + runner.gaList[runner.gaCursor].Steps();
	chkSolved->IsChecked = runner.gaList[runner.gaCursor].isSolved();
	txtSolverCursor->Text = runner.gaCursor + "/" + (runner.gaList.size() - 1);
	RefreshMaze(false);
	isStopped = false;
}

void GAMazeSolver::MainPage::btnPrev_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	runner.PrevSolver();
	txtSolverCursor->Text = runner.gaCursor + "/" + (runner.gaList.size() - 1);
	chkSolved->IsChecked = runner.gaList[runner.gaCursor].isSolved();
	txtSteps->Text = "Steps: " + runner.gaList[runner.gaCursor].Steps();
	RefreshMaze(false);
}

void GAMazeSolver::MainPage::btnNext_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	runner.NextSolver();
	txtSolverCursor->Text = runner.gaCursor + "/" + (runner.gaList.size() - 1);
	chkSolved->IsChecked = runner.gaList[runner.gaCursor].isSolved();
	txtSteps->Text = "Steps: " + runner.gaList[runner.gaCursor].Steps();
	RefreshMaze(false);
}

void MainPage::RefreshMaze(bool source)
{
	if (runner.gaCursor >= 0 && runner.gaCursor < runner.gaList.size())
	{
		for (int _Y = 0; _Y < MazeCell::MAZESIZE; _Y++)
		{
			for (int _X = 0; _X < MazeCell::MAZESIZE; _X++)
			{
				RefreshCell(_X, _Y, (int)runner.gaList[runner.gaCursor].solverBytes[_X][_Y], source);
			}
		}
	}
}



void GAMazeSolver::MainPage::btnRun_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	isStopped = false;
	btnStop->Content = "Stop";
	runnerTimer = ref new DispatcherTimer;
	runnerTimer->Tick += ref new EventHandler<Object^>(this, &MainPage::RefreshMazeTick);
	TimeSpan t;
	t.Duration = 100;
	runnerTimer->Interval = t;
	runnerTimer->Start();
}

void MainPage::RefreshMazeTick(Object^ sender, Object^ eventArgs)
{
	if (runner.epochs >= runner.m_maxEpochs)
		runnerTimer->Stop();
	btnStep_Click(nullptr, nullptr);
}


void GAMazeSolver::MainPage::btnStop_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (!isStopped)
	{
		isStopped = true;
		if (runnerTimer != nullptr)
			runnerTimer->Stop();
		btnStop->Content = "Reset";
	}
	else	// Reset
	{
		isStopped = false;
		runner.Reset();
		LoadFileAndInitialize();
	}
}


void GAMazeSolver::MainPage::MazeBrowse_PointerWheelChanged(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	if (e->GetCurrentPoint(nullptr)->Properties->MouseWheelDelta > 0)	// Scroll up, previous solver
		btnPrev_Click(nullptr, nullptr);

	else
		btnNext_Click(nullptr, nullptr);
}
