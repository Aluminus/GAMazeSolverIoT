Public Class GASolver

    Dim _startpos(1) As Byte
    Dim _endPos(1) As Byte
    Dim _isSolved As Boolean

    Dim solverBytes(MAZESIZE, MAZESIZE) As Byte

    Public ReadOnly Property StartPos As Byte()
        Get
            Return _startpos
        End Get
    End Property

    Public ReadOnly Property EndPos As Byte()
        Get
            Return _endPos
        End Get
    End Property

    Public ReadOnly Property GetBytes As Byte(,)
        Get
            Return solverBytes
        End Get
    End Property

    Public ReadOnly Property Steps As Integer
        Get
            Dim _steps As Integer = 0
            For _Y As Integer = 0 To MAZESIZE - 1
                For _X As Integer = 0 To MAZESIZE - 1
                    If solverBytes(_X, _Y) = CELLSTATE.Valid Then _steps += 1
                Next
            Next

            Return _steps
        End Get
    End Property

    Public ReadOnly Property isSolved As Boolean
        Get
            Return Solve(_startpos(0), _startpos(1))
        End Get
    End Property

    Private Function Solve(_X As Integer, _Y As Integer) As Boolean
        If solverBytes(_endPos(0), _endPos(1)) = CELLSTATE.Valid Then Return True

        If solverBytes(_X + 1, _Y) = CELLSTATE.Free Or solverBytes(_X + 1, _Y) = CELLSTATE.Start Or solverBytes(_X + 1, _Y) = CELLSTATE.Finish Then
            solverBytes(_X + 1, _Y) = CELLSTATE.Valid
            If Solve(_X + 1, _Y) Then Return True
        End If

        If solverBytes(_X - 1, _Y) = CELLSTATE.Free Or solverBytes(_X - 1, _Y) = CELLSTATE.Start Or solverBytes(_X - 1, _Y) = CELLSTATE.Finish Then
            solverBytes(_X - 1, _Y) = CELLSTATE.Valid
            If Solve(_X - 1, _Y) Then Return True
        End If

        If solverBytes(_X, _Y + 1) = CELLSTATE.Free Or solverBytes(_X, _Y + 1) = CELLSTATE.Start Or solverBytes(_X, _Y + 1) = CELLSTATE.Finish Then
            solverBytes(_X, _Y + 1) = CELLSTATE.Valid
            If Solve(_X, _Y + 1) Then Return True
        End If

        If solverBytes(_X, _Y - 1) = CELLSTATE.Free Or solverBytes(_X, _Y + 1) = CELLSTATE.Start Or solverBytes(_X, _Y + 1) = CELLSTATE.Finish Then
            solverBytes(_X, _Y - 1) = CELLSTATE.Valid
            If Solve(_X, _Y - 1) Then Return True
        End If

        Return False
    End Function

    Public Sub New(bytes01(,) As Byte, bytes02(,) As Byte, startPos As Byte(), endPos As Byte())
        _startpos = startPos
        _endPos = endPos

        For _Y As Integer = 0 To MAZESIZE - 1
            For _X As Integer = 0 To MAZESIZE - 1
                If bytes01(_X, _Y) = CELLSTATE.Wall Then solverBytes(_X, _Y) = bytes01(_X, _Y)
                If bytes01(_X, _Y) = CELLSTATE.FakeWall Then solverBytes(_X, _Y) = bytes01(_X, _Y)
            Next
        Next

        For _Y As Integer = 0 To MAZESIZE - 1
            For _X As Integer = 0 To MAZESIZE - 1
                If bytes02(_X, _Y) = CELLSTATE.Wall Then solverBytes(_X, _Y) = bytes02(_X, _Y)
                If bytes02(_X, _Y) = CELLSTATE.FakeWall Then solverBytes(_X, _Y) = bytes02(_X, _Y)
            Next
        Next

        For _Y As Integer = 0 To MAZESIZE - 1
            For _X As Integer = 0 To MAZESIZE - 1

                If solverBytes(_X, _Y) <> CELLSTATE.Wall Then
                    Randomize()
                    If Int(Rnd() * 100) Mod 99 = 0 Then
                        If Int(Rnd() * 100) Mod 99 = 0 Then
                            solverBytes(_X, _Y) = CELLSTATE.FakeWall
                        Else
                            solverBytes(_X, _Y) = CELLSTATE.Free
                        End If
                    End If
                End If

            Next
        Next

        solverBytes(startPos(0), startPos(1)) = CELLSTATE.Start
        solverBytes(endPos(0), endPos(1)) = CELLSTATE.Finish
    End Sub

    Public Sub New(sourceBytes(,) As Byte)
        For _Y As Integer = 0 To MAZESIZE - 1
            For _X As Integer = 0 To MAZESIZE - 1

                If sourceBytes(_X, _Y) = CELLSTATE.Start Then _startpos(0) = _X : _startpos(1) = _Y
                If sourceBytes(_X, _Y) = CELLSTATE.Finish Then _endPos(0) = _X : _endPos(1) = _Y

                If sourceBytes(_X, _Y) = CELLSTATE.Free Then
                    Randomize()
                    If Int(Rnd() * 100) Mod 50 = 0 Then
                        solverBytes(_X, _Y) = CELLSTATE.FakeWall
                    Else
                        solverBytes(_X, _Y) = CELLSTATE.Free
                    End If
                Else
                    solverBytes(_X, _Y) = sourceBytes(_X, _Y)
                End If

            Next
        Next

    End Sub
End Class
