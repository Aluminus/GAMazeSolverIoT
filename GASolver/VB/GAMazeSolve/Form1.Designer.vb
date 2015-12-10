<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Form1))
        Me.mazeSrc = New System.Windows.Forms.Panel()
        Me.btnInit = New System.Windows.Forms.Button()
        Me.mazeDest = New System.Windows.Forms.Panel()
        Me.Button2 = New System.Windows.Forms.Button()
        Me.Button3 = New System.Windows.Forms.Button()
        Me.lbSample = New System.Windows.Forms.Label()
        Me.btnStart = New System.Windows.Forms.Button()
        Me.btnStop = New System.Windows.Forms.Button()
        Me.Button6 = New System.Windows.Forms.Button()
        Me.Button7 = New System.Windows.Forms.Button()
        Me.StatusStrip1 = New System.Windows.Forms.StatusStrip()
        Me.lbEpoch = New System.Windows.Forms.ToolStripStatusLabel()
        Me.StatusStrip1.SuspendLayout()
        Me.SuspendLayout()
        '
        'mazeSrc
        '
        Me.mazeSrc.BackColor = System.Drawing.Color.DimGray
        Me.mazeSrc.Location = New System.Drawing.Point(9, 12)
        Me.mazeSrc.Name = "mazeSrc"
        Me.mazeSrc.Size = New System.Drawing.Size(300, 300)
        Me.mazeSrc.TabIndex = 0
        '
        'btnInit
        '
        Me.btnInit.BackColor = System.Drawing.Color.Orange
        Me.btnInit.Cursor = System.Windows.Forms.Cursors.Hand
        Me.btnInit.FlatAppearance.BorderColor = System.Drawing.Color.Orange
        Me.btnInit.FlatAppearance.MouseDownBackColor = System.Drawing.Color.DarkOrange
        Me.btnInit.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.btnInit.Font = New System.Drawing.Font("Tahoma", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.btnInit.ForeColor = System.Drawing.SystemColors.ControlLightLight
        Me.btnInit.Location = New System.Drawing.Point(111, 317)
        Me.btnInit.Name = "btnInit"
        Me.btnInit.Size = New System.Drawing.Size(62, 30)
        Me.btnInit.TabIndex = 1
        Me.btnInit.Text = "Init"
        Me.btnInit.UseVisualStyleBackColor = False
        '
        'mazeDest
        '
        Me.mazeDest.BackColor = System.Drawing.Color.DimGray
        Me.mazeDest.Location = New System.Drawing.Point(335, 12)
        Me.mazeDest.Name = "mazeDest"
        Me.mazeDest.Size = New System.Drawing.Size(300, 300)
        Me.mazeDest.TabIndex = 1
        '
        'Button2
        '
        Me.Button2.BackColor = System.Drawing.Color.Orange
        Me.Button2.Cursor = System.Windows.Forms.Cursors.Hand
        Me.Button2.FlatAppearance.BorderColor = System.Drawing.Color.Orange
        Me.Button2.FlatAppearance.MouseDownBackColor = System.Drawing.Color.DarkOrange
        Me.Button2.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.Button2.Font = New System.Drawing.Font("Tahoma", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Button2.ForeColor = System.Drawing.SystemColors.ControlLightLight
        Me.Button2.Location = New System.Drawing.Point(335, 318)
        Me.Button2.Name = "Button2"
        Me.Button2.Size = New System.Drawing.Size(39, 30)
        Me.Button2.TabIndex = 2
        Me.Button2.Text = "«"
        Me.Button2.UseVisualStyleBackColor = False
        '
        'Button3
        '
        Me.Button3.BackColor = System.Drawing.Color.Orange
        Me.Button3.Cursor = System.Windows.Forms.Cursors.Hand
        Me.Button3.FlatAppearance.BorderColor = System.Drawing.Color.Orange
        Me.Button3.FlatAppearance.MouseDownBackColor = System.Drawing.Color.DarkOrange
        Me.Button3.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.Button3.Font = New System.Drawing.Font("Tahoma", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Button3.ForeColor = System.Drawing.SystemColors.ControlLightLight
        Me.Button3.Location = New System.Drawing.Point(596, 318)
        Me.Button3.Name = "Button3"
        Me.Button3.Size = New System.Drawing.Size(39, 30)
        Me.Button3.TabIndex = 3
        Me.Button3.Text = "»"
        Me.Button3.UseVisualStyleBackColor = False
        '
        'lbSample
        '
        Me.lbSample.BackColor = System.Drawing.Color.Gainsboro
        Me.lbSample.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.lbSample.Font = New System.Drawing.Font("Microsoft Sans Serif", 6.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lbSample.Location = New System.Drawing.Point(377, 318)
        Me.lbSample.Name = "lbSample"
        Me.lbSample.Size = New System.Drawing.Size(216, 29)
        Me.lbSample.TabIndex = 4
        Me.lbSample.Text = "-- / --"
        Me.lbSample.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'btnStart
        '
        Me.btnStart.BackColor = System.Drawing.Color.Orange
        Me.btnStart.Cursor = System.Windows.Forms.Cursors.Hand
        Me.btnStart.Enabled = False
        Me.btnStart.FlatAppearance.BorderColor = System.Drawing.Color.Orange
        Me.btnStart.FlatAppearance.MouseDownBackColor = System.Drawing.Color.DarkOrange
        Me.btnStart.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.btnStart.Font = New System.Drawing.Font("Tahoma", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.btnStart.ForeColor = System.Drawing.SystemColors.ControlLightLight
        Me.btnStart.Location = New System.Drawing.Point(179, 317)
        Me.btnStart.Name = "btnStart"
        Me.btnStart.Size = New System.Drawing.Size(62, 30)
        Me.btnStart.TabIndex = 5
        Me.btnStart.Text = "Start"
        Me.btnStart.UseVisualStyleBackColor = False
        '
        'btnStop
        '
        Me.btnStop.BackColor = System.Drawing.Color.Orange
        Me.btnStop.Cursor = System.Windows.Forms.Cursors.Hand
        Me.btnStop.Enabled = False
        Me.btnStop.FlatAppearance.BorderColor = System.Drawing.Color.Orange
        Me.btnStop.FlatAppearance.MouseDownBackColor = System.Drawing.Color.DarkOrange
        Me.btnStop.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.btnStop.Font = New System.Drawing.Font("Tahoma", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.btnStop.ForeColor = System.Drawing.SystemColors.ControlLightLight
        Me.btnStop.Location = New System.Drawing.Point(247, 317)
        Me.btnStop.Name = "btnStop"
        Me.btnStop.Size = New System.Drawing.Size(62, 30)
        Me.btnStop.TabIndex = 6
        Me.btnStop.Text = "Stop"
        Me.btnStop.UseVisualStyleBackColor = False
        '
        'Button6
        '
        Me.Button6.BackColor = System.Drawing.Color.Orange
        Me.Button6.Cursor = System.Windows.Forms.Cursors.Hand
        Me.Button6.FlatAppearance.BorderColor = System.Drawing.Color.Orange
        Me.Button6.FlatAppearance.MouseDownBackColor = System.Drawing.Color.DarkOrange
        Me.Button6.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.Button6.Font = New System.Drawing.Font("Tahoma", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Button6.ForeColor = System.Drawing.SystemColors.ControlLightLight
        Me.Button6.Image = CType(resources.GetObject("Button6.Image"), System.Drawing.Image)
        Me.Button6.Location = New System.Drawing.Point(9, 317)
        Me.Button6.Name = "Button6"
        Me.Button6.Size = New System.Drawing.Size(30, 30)
        Me.Button6.TabIndex = 7
        Me.Button6.UseVisualStyleBackColor = False
        '
        'Button7
        '
        Me.Button7.BackColor = System.Drawing.Color.Orange
        Me.Button7.Cursor = System.Windows.Forms.Cursors.Hand
        Me.Button7.FlatAppearance.BorderColor = System.Drawing.Color.Orange
        Me.Button7.FlatAppearance.MouseDownBackColor = System.Drawing.Color.DarkOrange
        Me.Button7.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.Button7.Font = New System.Drawing.Font("Tahoma", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Button7.ForeColor = System.Drawing.SystemColors.ControlLightLight
        Me.Button7.Image = CType(resources.GetObject("Button7.Image"), System.Drawing.Image)
        Me.Button7.Location = New System.Drawing.Point(45, 317)
        Me.Button7.Name = "Button7"
        Me.Button7.Size = New System.Drawing.Size(30, 30)
        Me.Button7.TabIndex = 8
        Me.Button7.UseVisualStyleBackColor = False
        '
        'StatusStrip1
        '
        Me.StatusStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.lbEpoch})
        Me.StatusStrip1.Location = New System.Drawing.Point(0, 358)
        Me.StatusStrip1.Name = "StatusStrip1"
        Me.StatusStrip1.Size = New System.Drawing.Size(643, 22)
        Me.StatusStrip1.TabIndex = 9
        Me.StatusStrip1.Text = "StatusStrip1"
        '
        'lbEpoch
        '
        Me.lbEpoch.BackColor = System.Drawing.Color.Transparent
        Me.lbEpoch.Name = "lbEpoch"
        Me.lbEpoch.Size = New System.Drawing.Size(52, 17)
        Me.lbEpoch.Text = "Epoch: 0"
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackColor = System.Drawing.Color.White
        Me.ClientSize = New System.Drawing.Size(643, 380)
        Me.Controls.Add(Me.StatusStrip1)
        Me.Controls.Add(Me.Button7)
        Me.Controls.Add(Me.Button6)
        Me.Controls.Add(Me.btnStop)
        Me.Controls.Add(Me.btnStart)
        Me.Controls.Add(Me.lbSample)
        Me.Controls.Add(Me.Button3)
        Me.Controls.Add(Me.Button2)
        Me.Controls.Add(Me.mazeDest)
        Me.Controls.Add(Me.btnInit)
        Me.Controls.Add(Me.mazeSrc)
        Me.DoubleBuffered = True
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.Name = "Form1"
        Me.Text = "Genetic Algorithm for Optimal Maze Solution"
        Me.StatusStrip1.ResumeLayout(False)
        Me.StatusStrip1.PerformLayout()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents mazeSrc As System.Windows.Forms.Panel
    Friend WithEvents btnInit As System.Windows.Forms.Button
    Friend WithEvents mazeDest As System.Windows.Forms.Panel
    Friend WithEvents Button2 As System.Windows.Forms.Button
    Friend WithEvents Button3 As System.Windows.Forms.Button
    Friend WithEvents lbSample As System.Windows.Forms.Label
    Friend WithEvents btnStart As System.Windows.Forms.Button
    Friend WithEvents btnStop As System.Windows.Forms.Button
    Friend WithEvents Button6 As System.Windows.Forms.Button
    Friend WithEvents Button7 As System.Windows.Forms.Button
    Friend WithEvents StatusStrip1 As System.Windows.Forms.StatusStrip
    Friend WithEvents lbEpoch As System.Windows.Forms.ToolStripStatusLabel

End Class
