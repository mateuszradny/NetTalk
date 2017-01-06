using Microsoft.Practices.Unity;
using NetTalk.ViewModels;
using System.Windows;

namespace NetTalk.Views
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainView : Window
    {
        public MainView()
        {
            InitializeComponent();
            this.DataContext = UnityConfig.GetConfiguredContainer().Resolve<MainViewModel>();
        }
    }
}