using NetTalk.Model;
using NetTalk.Protocol.Responses;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace NetTalk.Contracts.Services
{
    public interface IClientService
    {
        string AuthToken { get; }

        Task<AddContactResult> AddContactAsync(string contactName);

        Task<List<Contact>> GetContacts();

        Task<LoginResult> LoginAsync(string userName, string password);

        Task<RegistrationResult> RegisterAsync(string userName, string password);

        Task<SendMessageResult> SendMessageAsync(string recipient, string message);

        Task<List<Message>> ReceiveMessages();
    }
}