using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

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
