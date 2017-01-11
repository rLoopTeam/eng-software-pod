Namespace SIL3.rLoop.rPodControl.Panels.Settings

    ''' <summary>
    ''' Top level settings panel
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

        Private m_pnlSettings__File As SIL3.rLoop.rPodControl.Panels.Settings.FilePaths
        Private m_pnlSettings__Network As SIL3.rLoop.rPodControl.Panels.Settings.Network
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

            Me.m_iBarIndex = Me.m_pExplorer.Bar__Add("Settings")
            Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "File Paths")
            Me.m_pExplorer.SubItem__Add_LinkItem(Me.m_iBarIndex, "Network Settings")

            'add the panels before the bar so as we have docking working well.
            Me.m_pnlSettings__File = New SIL3.rLoop.rPodControl.Panels.Settings.FilePaths("File Paths")
            pf.Controls.Add(Me.m_pnlSettings__File)
            Me.m_pnlSettings__Network = New SIL3.rLoop.rPodControl.Panels.Settings.Network("Network Settings")
            pf.Controls.Add(Me.m_pnlSettings__Network)

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
            Me.m_pnlSettings__File.Panel__HideShow(sText)
            Me.m_pnlSettings__Network.Panel__HideShow(sText)
        End Sub
#End Region '#Region "PANEL HELPERS"

#Region "EXPLORER BAR"
        ''' <summary>
        ''' Called when a link is clicked
        ''' </summary>
        ''' <param name="sText"></param>
        ''' <remarks></remarks>
        Private Sub LinkBar_LinkClick(ByVal sText As String)
            Me.m_pnlSettings__File.Panel__HideShow(sText)
            Me.m_pnlSettings__Network.Panel__HideShow(sText)
        End Sub
#End Region '#Region "EXPLORER BAR"


#Region "SETTINGS"
        Public Function Get__DataLogDir() As String
            Return Me.m_pnlSettings__File.Get__DataLogDir
        End Function
#End Region


    End Class

End Namespace
