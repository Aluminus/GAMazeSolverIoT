Public Class MazeCell
    Inherits PictureBox

    Dim _STATUS As Byte = 0
    Dim _MATX As Byte = 0
    Dim _MATY As Byte = 0

    Public Property CellStatus As Byte
        Get
            Return _STATUS
        End Get
        Set(value As Byte)
            _STATUS = value
        End Set
    End Property

    Public ReadOnly Property CellBrush As Color
        Get
            Select Case CellStatus
                Case CELLSTATE.Free
                    Return Color.Black
                Case CELLSTATE.Valid
                    Return Color.Violet
                Case CELLSTATE.Start
                    Return Color.Green
                Case CELLSTATE.Finish
                    Return Color.Red
                Case CELLSTATE.Wall
                    Return Color.Gray
                Case CELLSTATE.FakeWall
                    Return Color.Yellow
            End Select
        End Get
    End Property

    Public Property MatX As Byte
        Get
            Return _MATX
        End Get
        Set(value As Byte)
            _MATX = value
        End Set
    End Property

    Public Property MatY As Byte
        Get
            Return _MATY
        End Get
        Set(value As Byte)
            _MATY = value
        End Set
    End Property

    Public ReadOnly Property StringMatrix As String
        Get
            Return _MATX.ToString & ";" & _MATY.ToString
        End Get
    End Property
End Class
