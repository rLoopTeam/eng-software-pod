Namespace SIL3.rLoop.rPodControl.Panels.Brakes

    ''' <summary>
    ''' Top level brakes panel
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Top

#Region "MEMBERS"
        ''' <summary>
        ''' Our application explorer bar
        ''' </summary>
        ''' <remarks></remarks>
        Private m_pExplorer As SIL3.ApplicationSupport.ExplorerBarHelper

        ''' <summary>
        ''' The index of our category in the explorer bar
        ''' </summary>
        ''' <remarks></remarks>
        Private m_iBarIndex As Integer

        Private m_pnlBrakes__Switches As SIL3.rLoop.rPodControl.Panels.Brakes.Switches

#End Region '#Region "MEMBERS"

#Region "NEW"
        ''' <summary>
        ''' New instance
        ''' </summary>
        ''' <param name="pf"></param>
        ''' <remarks></remarks>
        Public Sub New(ByRef pf As Windows.Forms.Form, ByRef pExplorer As SIL3.ApplicationSupport.ExplorerBarHelper)

            'setup our explorer bar
            Me.m_pExplorer = pExplorer

            Me.m_iBarIndex = Me.m_pExplorer.Bar__Add("Flight Control")
            Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "Accelerometers")

            Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "Brakes - Switches")


            'add the panels before the bar so as we have docking working well.
            Me.m_pnlBrakes__Switches = New SIL3.rLoop.rPodControl.Panels.Brakes.Switches("Brakes - Switches")
            pf.Controls.Add(Me.m_pnlBrakes__Switches)


            AddHandler Me.m_pExplorer.LinkClick, AddressOf Me.LinkBar_LinkClick

        End Sub

#End Region '#Region "NEW"

#Region "PANEL HELPERS"
        ''' <summary>
        ''' How or hide this panel if our text matches
        ''' </summary>
        ''' <param name="sText"></param>
        ''' <remarks></remarks>
        Public Sub Panel__HideShow(sText As String)
            Me.m_pnlBrakes__Switches.Panel__HideShow(sText)

        End Sub
#End Region '#Region "PANEL HELPERS"

#Region "EXPLORER BAR"
        ''' <summary>
        ''' Called when a link is clicked
        ''' </summary>
        ''' <param name="sText"></param>
        ''' <remarks></remarks>
        Private Sub LinkBar_LinkClick(ByVal sText As String)
            Me.m_pnlBrakes__Switches.Panel__HideShow(sText)

        End Sub
#End Region '#Region "EXPLORER BAR"

    End Class

End Namespace
