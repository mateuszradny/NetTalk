using NetTalk.Contracts.Services;
using NetTalk.Model;
using NetTalk.Protocol.Requests;
using NetTalk.Protocol.Responses;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace NetTalk.Services
{
    public class ClientService : IClientService
    {
        private readonly ICommunicationService communicationService;

        public ClientService(ICommunicationService communicationService)
        {
            this.communicationService = communicationService;
        }

        public string AuthToken { get; private set; }

        public async Task<AddContactResult> AddContactAsync(string contactName)
        {
            if (AuthToken == null)
                throw new InvalidOperationException("The user is not authenticated");

            AddContactRequest request = new AddContactRequest(AuthToken, contactName);
            AddContactResponse response = await communicationService.SendAsync(request) as AddContactResponse;

            return response.Result;
        }

        public async Task<List<Contact>> GetContacts()
        {
            GetContactsRequest request = new GetContactsRequest(AuthToken);
            GetContactsResponse response = await communicationService.SendAsync(request) as GetContactsResponse;

            return response.Contacts;
        }

        public async Task<LoginResult> LoginAsync(string userName, string password)
        {
            LoginRequest request = new LoginRequest(userName, password);
            LoginResponse response = await communicationService.SendAsync(request) as LoginResponse;

            if (response.Result == LoginResult.Ok)
                AuthToken = response.AuthToken;

            return response.Result;
        }

        public async Task<RegistrationResult> RegisterAsync(string userName, string password)
        {
            RegistrationRequest request = new RegistrationRequest(userName, password);
            RegistrationResponse response = await communicationService.SendAsync(request) as RegistrationResponse;

            return response.Result;
        }

        public async Task<SendMessageResult> SendMessageAsync(string recipient, string message)
        {
            SendMessageRequest request = new SendMessageRequest(AuthToken, message, recipient);
            SendMessageResponse response = await communicationService.SendAsync(request) as SendMessageResponse;

            return response.Result;
        }

        public async Task<List<Message>> ReceiveMessages()
        {
            ReceiveMessagesRequest request = new ReceiveMessagesRequest(AuthToken);
            ReceiveMessagesResponse response = await communicationService.SendAsync(request) as ReceiveMessagesResponse;

            return response.Messages;
        }
    }
}