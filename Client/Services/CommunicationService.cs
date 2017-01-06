using NetTalk.Contracts.Services;
using NetTalk.Exceptions;
using NetTalk.Protocol.Requests;
using NetTalk.Protocol.Responses;
using System;
using System.Configuration;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace NetTalk.Services
{
    public class CommunicationService : ICommunicationService
    {
        private const string AddressKey = "Address";
        private const string PortKey = "Port";

        public async Task<ResponseBase> SendAsync(RequestBase request)
        {
            return await Task.Run<ResponseBase>(() =>
            {
                using (Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
                {
                    socket.Connect(IPAddress.Parse(ConfigurationManager.AppSettings[AddressKey]), int.Parse(ConfigurationManager.AppSettings[PortKey]));

                    using (NetworkStream stream = new NetworkStream(socket))
                    using (BinaryWriter writer = new BinaryWriter(stream, Encoding.ASCII))
                    using (BinaryReader reader = new BinaryReader(stream, Encoding.ASCII))
                    {
                        WriteRequest(request, writer);
                        return ReadResponse(reader);
                    }
                }
            });
        }

        private static ResponseBase ReadResponse(BinaryReader reader)
        {
            int responseSize = reader.ReadInt32();
            byte[] bytes = reader.ReadBytes(responseSize);

            ResponseType responseType = (ResponseType)BitConverter.ToInt32(bytes, 0);
            switch (responseType)
            {
            case ResponseType.RegistrationResult:
                return RegistrationResponse.Parse(bytes);

            case ResponseType.LoginResult:
                return LoginResponse.Parse(bytes);

            case ResponseType.AddContact:
                return AddContactResponse.Parse(bytes);

            case ResponseType.GetContacts:
                return GetContactsResponse.Parse(bytes);

            case ResponseType.SendMessage:
                return SendMessageResponse.Parse(bytes);

            case ResponseType.ReceiveMessages:
                return ReceiveMessagesResponse.Parse(bytes);

            case ResponseType.Ok:
            case ResponseType.InvalidAuthToken:
                throw new NotImplementedException();

            case ResponseType.ServerError:
                throw new ServerErrorException(ServerErrorResponse.Parse(bytes).ErrorMessage);

            default:
                throw new InvalidOperationException("Invalid type of response");
            }
        }

        private static void WriteRequest(RequestBase request, BinaryWriter writer)
        {
            byte[] bytes = request.ToBytes();
            writer.Write(bytes.Length);
            writer.Write(bytes);
        }
    }
}