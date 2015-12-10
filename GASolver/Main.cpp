// GASolver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GASolver.h"
#include "GARunner.h"

void GenerateMaze()
{
	int _TOP = 0;
	int _LEFT = 0;

	for (int _Y = 0; _Y < MazeCell::MAZESIZE; _Y++)
	{
		for (int _X = 0; _X < MazeCell::MAZESIZE; _X++)
		{
			MazeCell pb;
			/*pb.Name = container.Name & _Y.ToString("00") & _X.ToString("00");
			pb.Top = _TOP;
			pb.Left = _LEFT;
			pb.Width = MazeCell::MAZESIDE;
			pb.Height = MazeCell::MAZESIDE;
			pb.BackColor = Color.Black;
			pb.BorderStyle = BorderStyle.FixedSingle;
			pb.Cursor = Cursors.Hand;*/
			pb.SetMatX(_X);
			pb.SetMatY(_Y);
			/*pb.Click = MazeClickCell;
			pb.Paint = MazePaintCell;*/
			_LEFT += MazeCell::MAZESIDE;
			/*container.Controls.Add(pb)*/
		}
		_LEFT = 0;
		_TOP += MazeCell::MAZESIDE;
	}
}

void MazeClickCell(MazeCell* pb)
{
	/*pb->SetCellStatus(pb->GetCellStatus() + MazeCell::CELLSTATE::Wall);
	if (pb->GetCellStatus() > MazeCell::CELLSTATE::Valid)
		pb->SetCellStatus(MazeCell::CELLSTATE::Free);

	sourceMaze[pb->GetMatX()][pb->GetMatY()] = pb->GetCellStatus();
	pb->BackColor = pb->CellBrush*/
}

void MazePaintCell(MazeCell* pb)
{
   /* With e.Graphics
	      .DrawString(pb.StringMatrix.Replace(";", ControlChars.CrLf), New Font("Tahoma", 4), Brushes.LightGray, 0, 0)
   End With*/
}

void MazePaintItem()
{
	//if (gaCursor < 0)
	//	gaCursor = gaList.size() - 1;
	//if (gaCursor > gaList.size() - 1)
	//	gaCursor = 0;

	//GASolver gaElement = gaList[gaCursor];

	//lbSample.Text = "Solution " & (gaCursor + 1).ToString & " / " & gaList.Count.ToString & ControlChars.CrLf & _
	//"IsSolved = " & gaElement.isSolved.ToString & ", Steps: " & gaElement.Steps.ToString

	//for (auto& pb : containter)
	//{
	//pb.CellStatus = gaElement.GetBytes(pb.MatX, pb.MatY)
	//pb.BackColor = pb.CellBrush
	//} 
}

void Button6_Click()
{
	/*Using sd As New SaveFileDialog
		With sd
		.Title = "Save Maze"
		.Filter = "Text Files(*.txt)|*.txt"
		.AddExtension = True
		If.ShowDialog = Windows.Forms.DialogResult.OK Then

		Using sw As New StreamWriter(.FileName)
		For _Y As Integer = 0 To MAZESIZE - 1
		For _X As Integer = 0 To MAZESIZE - 1
		sw.WriteLine(_X & ";" & _Y & ";" & sourceMaze(_X, _Y))
		Next
		Next
		End Using

		End If

		End With
		End Using*/
}

void btnStop_Click()
{
	//bRun = false;

	//btnStart.Enabled = True;
	//btnStop.Enabled = False;
}

void btnStart_Click() 
{
	//btnStart.Enabled = False;
	//btnStop.Enabled = True;
}

int _tmain(int argc, _TCHAR* argv[])
{
	GenerateMaze();	// Source
	GenerateMaze();	// Destination
	GARunner r{1000, 500};
	r.Load(_T("test_maze.txt"));
	r.Print(-1);
	r.InitializeSolvers();
	r.Run();
	return 0;
}


