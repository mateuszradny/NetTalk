using Microsoft.Practices.Unity;
using NetTalk.ViewModels;
using System.Windows.Controls;

namespace NetTalk.Views
{
    /// <summary>
    /// Interaction logic for ChatView.xaml
    /// </summary>
    public partial class ChatView : UserControl
    {
        public ChatView()
        {
            InitializeComponent();
            DataContext = UnityConfig.GetConfiguredContainer().Resolve<ChatViewModel>();
        }
    }
}