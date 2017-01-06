using NetTalk.Model;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace NetTalk.Protocol.Responses
{
    public class ReceiveMessagesResponse : ResponseBase
    {
        public ReceiveMessagesResponse(List<Message> messages)
        {
            Messages = messages;
        }

        public override ResponseType ResponseType { get; } = ResponseType.ReceiveMessages;

        public List<Message> Messages { get; private set; }

        public static ReceiveMessagesResponse Parse(byte[] bytes)
        {
            using (MemoryStream stream = new MemoryStream(bytes))
            using (BinaryReader reader = new BinaryReader(stream, Encoding.ASCII))
            {
                ResponseType responseType = (ResponseType)reader.ReadInt32();
                if (responseType != ResponseType.ReceiveMessages)
                    throw new InvalidOperationException("Invalid type of response");

                int messageCount = reader.ReadInt32();
                List<Message> messages = new List<Message>();
                for (int i = 0; i < messageCount; i++)
                {
                    Message message = new Message();
                    message.Sender = Encoding.ASCII.GetString(reader.ReadBytes(reader.ReadInt32()));
                    message.PostDate = UnixTimeStampToDateTime(reader.ReadInt64());
                    message.Body = Encoding.ASCII.GetString(reader.ReadBytes(reader.ReadInt32()));
                    message.Direction = MessageDirection.Incoming;

                    messages.Add(message);
                }

                return new ReceiveMessagesResponse(messages);
            }
        }

        public static DateTime UnixTimeStampToDateTime(long unixTimeStamp)
        {
            DateTime dateTime = new DateTime(1970, 1, 1, 0, 0, 0, 0, DateTimeKind.Utc);
            dateTime = dateTime.AddSeconds(unixTimeStamp).ToLocalTime();
            return dateTime;
        }
    }
}