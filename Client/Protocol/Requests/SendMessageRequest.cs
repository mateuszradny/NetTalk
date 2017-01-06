using System;
using System.IO;
using System.Text;

namespace NetTalk.Protocol.Requests
{
    public class SendMessageRequest : AuthenticatedRequest
    {
        public SendMessageRequest(string authToken, string message, string recipientName) : base(authToken, RequestType.SendMessage)
        {
            if (string.IsNullOrWhiteSpace(message))
                throw new ArgumentException("Invalid message");

            if (string.IsNullOrWhiteSpace(recipientName))
                throw new ArgumentException("Invalid recipient name");

            Message = message;
            Recipient = recipientName;
        }

        public string Message { get; private set; }
        public string Recipient { get; private set; }

        public override byte[] ToBytes()
        {
            using (MemoryStream stream = new MemoryStream())
            using (BinaryWriter writer = new BinaryWriter(stream))
            {
                writer.Write((int)RequestType);
                writer.Write(AuthToken.Length);
                writer.Write(Encoding.ASCII.GetBytes(AuthToken));
                writer.Write(Recipient.Length);
                writer.Write(Encoding.ASCII.GetBytes(Recipient));
                writer.Write(Message.Length);
                writer.Write(Encoding.ASCII.GetBytes(Message));

                return stream.ToArray();
            }
        }
    }
}