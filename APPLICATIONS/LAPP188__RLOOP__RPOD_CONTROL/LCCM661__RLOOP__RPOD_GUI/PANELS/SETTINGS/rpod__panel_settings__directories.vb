Namespace SIL3.rLoop.rPodControl.Panels.Settings

    ''' <summary>
    ''' File Path Locations settings
    ''' </summary>
    ''' <remarks></remarks>
    Public Class FilePaths
        Inherits SIL3.ApplicationSupport.PanelTemplate

#Region "MEMBERS"
        Private m_txtLogRoot As SIL3.ApplicationSupport.TextBoxHelper

#End Region '#Region "MEMBERS"

#Region "NEW"
        ''' <summary>
        ''' New instance
        ''' </summary>
        ''' <param name="sPanelText"></param>
        ''' <remarks></remarks>
        Public Sub New(sPanelText As String)
            MyBase.New(sPanelText)
            Me.LayoutPanel()
        End Sub
#End Region '#Region "NEW"

#Region "PANEL LAYOUT"
        ''' <summary>
        ''' Create our layout prior to being shown
        ''' </summary>
        ''' <remarks></remarks>
        Public Overrides Sub LayoutPanel()

            Dim l1 As New SIL3.ApplicationSupport.LabelHelper(10, 10, "Data Logging Folder", Me.m_pInnerPanel)
            Me.m_txtLogRoot = New SIL3.ApplicationSupport.TextBoxHelper(500, l1)
            Me.m_txtLogRoot.Persist__Set(Types.eSIL3CompanyType.SIL3__APP_PATH, "data_log_folder.txt")


        End Sub
#End Region '#Region "PANEL LAYOUT"

#Region "GET"
        ''' <summary>
        ''' Return the data logging directory
        ''' </summary>
        ''' <returns></returns>
        Public Function Get__DataLogDir() As String
            Dim sText As String = Me.m_txtLogRoot.Text
            If sText.EndsWith("\") = False Then
                sText = sText & "\"
            End If
            Return sText
        End Function
#End Region

    End Class


End Namespace
