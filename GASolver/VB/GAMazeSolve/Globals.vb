Module Globals

    Public Const MAZESIZE As Byte = 20
    Public Const MAZESIDE As Byte = 15

    Public Enum CELLSTATE
        Free = 0
        Wall = 1
        Start = 2
        Finish = 3
        Valid = 4
        FakeWall = 5
    End Enum

End Module
