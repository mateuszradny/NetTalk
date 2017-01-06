using NetTalk.Exceptions;
using System.Windows;
using System.Windows.Threading;

namespace NetTalk
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        public App()
        {
            DispatcherUnhandledException += App_DispatcherUnhandledException;
        }

        private void App_DispatcherUnhandledException(object sender, DispatcherUnhandledExceptionEventArgs e)
        {
            ServerErrorException ex = e.Exception as ServerErrorException;
            if (ex != null)
            {
                MessageBox.Show(ex.Message, "Server Error", MessageBoxButton.OK, MessageBoxImage.Error);
                e.Handled = true;
            }
        }

        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);
        }
    }
}