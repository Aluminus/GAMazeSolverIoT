Imports System.IO
Imports System.Runtime.Serialization.Formatters.Binary

Public Class Form1

    Dim sourceMaze(MAZESIZE, MAZESIZE) As Byte
    Dim _startPos(1) As Byte
    Dim _endPos(1) As Byte

    Dim bRun As Boolean = False
    Dim epochs As Long = 0
    Dim gaList As List(Of GASolver)
    Dim gaCursor As Integer = 0

    Private Sub GenerateMaze(container As Panel)
        Dim _TOP As Integer = 0
        Dim _LEFT As Integer = 0

        For _Y As Integer = 0 To MAZESIZE - 1
            For _X As Integer = 0 To MAZESIZE - 1

                Dim pb As New MazeCell
                With pb
                    .Name = container.Name & _Y.ToString("00") & _X.ToString("00")
                    .Top = _TOP
                    .Left = _LEFT
                    .Width = MAZESIDE
                    .Height = MAZESIDE
                    .BackColor = Color.Black
                    .BorderStyle = BorderStyle.FixedSingle
                    .Cursor = Cursors.Hand

                    .MatX = _X
                    .MatY = _Y

                    AddHandler pb.Click, AddressOf MazeClickCell
                    'AddHandler pb.Paint, AddressOf MazePaintCell
                End With

                _LEFT += MAZESIDE
                container.Controls.Add(pb)
            Next
            _LEFT = 0
            _TOP += MAZESIDE
        Next
    End Sub

    Private Sub MazeClickCell(sender As Object, e As EventArgs)
        Dim pb As MazeCell = CType(sender, MazeCell)

        pb.CellStatus += 1
        If pb.CellStatus > CELLSTATE.Valid Then pb.CellStatus = CELLSTATE.Free

        sourceMaze(pb.MatX, pb.MatY) = pb.CellStatus
        pb.BackColor = pb.CellBrush
    End Sub

    'Private Sub MazePaintCell(sender As Object, e As PaintEventArgs)
    'Dim pb As MazeCell = CType(sender, MazeCell)
    '    With e.Graphics
    '        .DrawString(pb.StringMatrix.Replace(";", ControlChars.CrLf), New Font("Tahoma", 4), Brushes.LightGray, 0, 0)
    '    End With
    'End Sub

    Private Sub MazePaintItem(container As Panel)
        If gaCursor < 0 Then gaCursor = gaList.Count - 1
        If gaCursor > gaList.Count - 1 Then gaCursor = 0

        Dim gaElement As GASolver = (From ga As GASolver In gaList Order By ga.isSolved Descending, ga.Steps Ascending)(gaCursor)

        lbSample.Text = "Solution " & (gaCursor + 1).ToString & " / " & gaList.Count.ToString & ControlChars.CrLf & _
                        "IsSolved = " & gaElement.isSolved.ToString & ", Steps: " & gaElement.Steps.ToString

        For Each pb As MazeCell In container.Controls
            pb.CellStatus = gaElement.GetBytes(pb.MatX, pb.MatY)
            pb.BackColor = pb.CellBrush
        Next
    End Sub

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        GenerateMaze(mazeSrc)
        GenerateMaze(mazeDest)
    End Sub

    Private Sub btnInit_Click(sender As Object, e As EventArgs) Handles btnInit.Click
        epochs = 0

        For _Y As Integer = 0 To MAZESIZE - 1
            For _X As Integer = 0 To MAZESIZE - 1
                If sourceMaze(_X, _Y) = CELLSTATE.Start Then _startPos(0) = _X : _startPos(1) = _Y
                If sourceMaze(_X, _Y) = CELLSTATE.Finish Then _endPos(0) = _X : _endPos(1) = _Y
            Next
        Next

        gaList = New List(Of GASolver)
        For ii As Integer = 0 To 999
            gaList.Add(New GASolver(sourceMaze))
        Next

        gaCursor = 0
        MazePaintItem(mazeDest)

        btnStart.Enabled = True
        btnStop.Enabled = False
    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        gaCursor -= 1
        MazePaintItem(mazeDest)
    End Sub

    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Button3.Click
        gaCursor += 1
        MazePaintItem(mazeDest)
    End Sub

    Private Sub Button6_Click(sender As Object, e As EventArgs) Handles Button6.Click
        Using sd As New SaveFileDialog
            With sd
                .Title = "Save Maze"
                .Filter = "Text Files(*.txt)|*.txt"
                .AddExtension = True
                If .ShowDialog = Windows.Forms.DialogResult.OK Then

                    Using sw As New StreamWriter(.FileName)
                        For _Y As Integer = 0 To MAZESIZE - 1
                            For _X As Integer = 0 To MAZESIZE - 1
                                sw.WriteLine(_X & ";" & _Y & ";" & sourceMaze(_X, _Y))
                            Next
                        Next
                    End Using

                End If

            End With
        End Using
    End Sub

    Private Sub Button7_Click(sender As Object, e As EventArgs) Handles Button7.Click
        Using od As New OpenFileDialog
            With od
                .Title = "Load Maze"
                .Filter = "Text Files(*.txt)|*.txt"
                .AddExtension = True
                If .ShowDialog = Windows.Forms.DialogResult.OK Then

                    Using sr As New StreamReader(.FileName)
                        While Not sr.EndOfStream
                            Dim pars() As String = sr.ReadLine.Split(";")
                            Dim _X As Integer = Integer.Parse(pars(0))
                            Dim _Y As Integer = Integer.Parse(pars(1))
                            Dim _S As Integer = Integer.Parse(pars(2))

                            sourceMaze(_X, _Y) = _S
                            Dim pb As MazeCell = CType(mazeSrc.Controls("mazeSrc" & _Y.ToString("00") & _X.ToString("00")), MazeCell)
                            pb.CellStatus = _S
                            pb.BackColor = pb.CellBrush
                        End While
                    End Using

                End If

            End With
        End Using
    End Sub

    Private Sub btnStop_Click(sender As Object, e As EventArgs) Handles btnStop.Click
        bRun = False

        btnStart.Enabled = True
        btnStop.Enabled = False
    End Sub

    Private Sub btnStart_Click(sender As Object, e As EventArgs) Handles btnStart.Click
        btnStart.Enabled = False
        btnStop.Enabled = True

        bRun = True
        While bRun

            Dim bestMazes As IEnumerable(Of GASolver) = From ga As GASolver In gaList Where ga.isSolved = True Order By ga.Steps Ascending Take (2)

            Dim sample01 As New GASolver(bestMazes(0).GetBytes, bestMazes(1).GetBytes, _startPos, _endPos)
            Dim sample02 As New GASolver(bestMazes(1).GetBytes, bestMazes(0).GetBytes, _startPos, _endPos)
            gaList.Add(sample01)
            gaList.Add(sample02)

            Dim worstMazes As IEnumerable(Of GASolver) = From ga As GASolver In gaList Order By ga.Steps Descending
            gaList.Remove(worstMazes(0))
            gaList.Remove(worstMazes(1))

            MazePaintItem(mazeDest)
            Application.DoEvents()

            epochs += 1
            lbEpoch.Text = "Epoch: " & epochs.ToString
        End While
    End Sub

End Class
