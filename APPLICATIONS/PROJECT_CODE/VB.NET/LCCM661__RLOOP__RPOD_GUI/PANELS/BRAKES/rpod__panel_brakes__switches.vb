Namespace SIL3.rLoop.rPodControl.Panels.Brakes

    ''' <summary>
    ''' Brake Switch Monitoring
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Switches
        Inherits SIL3.ApplicationSupport.PanelTemplate

#Region "MEMBERS"

        Private m_txtFaultFlags As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtLeftRetract As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtLeftExtend As SIL3.ApplicationSupport.TextBoxHelper

        Private m_txtRightRetract As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtRightExtend As SIL3.ApplicationSupport.TextBoxHelper

        Private m_txtLeftState As SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtRightState As SIL3.ApplicationSupport.TextBoxHelper

#End Region '#Region "MEMBERS"

#Region "NEW"
        ''' <summary>
        ''' New instance
        ''' </summary>
        ''' <param name="sPanelText"></param>
        ''' <remarks></remarks>
        Public Sub New(sPanelText As String)
            MyBase.New(sPanelText)

        End Sub
#End Region '#Region "NEW"

#Region "PANEL LAYOUT"
        ''' <summary>
        ''' Create our layout prior to being shown
        ''' </summary>
        ''' <remarks></remarks>
        Public Overrides Sub LayoutPanel()

            Dim l1 As New SIL3.ApplicationSupport.LabelHelper(10, 10, "Fault Flags", Me.m_pInnerPanel)
            Me.m_txtFaultFlags = New SIL3.ApplicationSupport.TextBoxHelper(100, l1)

            Dim l2a As New SIL3.ApplicationSupport.LabelHelper("Individual Switch States", Me.m_txtFaultFlags)

            Dim l2 As New SIL3.ApplicationSupport.LabelHelper("Left Retract", l2a)
            Me.m_txtLeftRetract = New SIL3.ApplicationSupport.TextBoxHelper(100, l2)

            Dim l3 As New SIL3.ApplicationSupport.LabelHelper("Left Extend", Me.m_txtLeftRetract)
            Me.m_txtLeftExtend = New SIL3.ApplicationSupport.TextBoxHelper(100, l3)

            Dim l4 As New SIL3.ApplicationSupport.LabelHelper("Right Retract")
            l4.Layout__AboveRightControl(l2, Me.m_txtLeftRetract)
            Me.m_txtRightRetract = New SIL3.ApplicationSupport.TextBoxHelper(100, l4)

            Dim l5 As New SIL3.ApplicationSupport.LabelHelper("Rigth Extend", Me.m_txtRightRetract)
            Me.m_txtRightExtend = New SIL3.ApplicationSupport.TextBoxHelper(100, l5)


            Dim l6 As New SIL3.ApplicationSupport.LabelHelper("Brake States", Me.m_txtLeftExtend)

            Dim l7 As New SIL3.ApplicationSupport.LabelHelper("Left State", l6)
            Me.m_txtLeftState = New SIL3.ApplicationSupport.TextBoxHelper(100, l7)

            Dim l8 As New SIL3.ApplicationSupport.LabelHelper("Right State")
            l8.Layout__AboveRightControl(l7, Me.m_txtLeftState)
            Me.m_txtRightState = New SIL3.ApplicationSupport.TextBoxHelper(100, l8)

        End Sub
#End Region '#Region "PANEL LAYOUT"

    End Class


End Namespace
