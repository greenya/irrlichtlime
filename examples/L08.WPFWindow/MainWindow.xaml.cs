using System.Windows;

namespace L08.WPFWindow
{
	public partial class MainWindow : Window
	{
		WinFormsUserControl userControl;

		public MainWindow()
		{
			InitializeComponent();
		}

		private void Window_Loaded(object sender, RoutedEventArgs e)
		{
			userControl = new WinFormsUserControl();
			wfHost.Child = userControl;
		}

		private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
		{
			if (userControl.IsRendering)
				userControl.Shutdown();
		}

		private void buttonClose_Click(object sender, RoutedEventArgs e)
		{
			Close();
		}

		private void checkboxNotifyResizes_Checked(object sender, RoutedEventArgs e)
		{
			if (userControl != null)
				userControl.IsNotifyResizes = checkboxNotifyResizes.IsChecked ?? false;
		}

		private void checkboxDockViewport_Checked(object sender, RoutedEventArgs e)
		{
			if (wfHost != null)
			{
				wfHost.Width = (bool)checkboxDockViewport.IsChecked ? double.NaN : wfHost.ActualWidth;
				wfHost.Height = (bool)checkboxDockViewport.IsChecked ? double.NaN : wfHost.ActualHeight;
			}
		}
	}
}
