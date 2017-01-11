
Public Class Form1
    Dim pX As SIL3.rLoop.rPodControl.Toolbox

    Private Sub Form1_FormClosing(sender As Object, e As System.Windows.Forms.FormClosingEventArgs) Handles Me.FormClosing
        pX.Destroy()
    End Sub


    Private Sub Form1_Load(sender As Object, e As System.EventArgs) Handles Me.Load
        pX = New SIL3.rLoop.rPodControl.Toolbox(Me)
    End Sub

End Class
