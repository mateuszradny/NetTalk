using System;
using System.IO;
using System.Text;

namespace NetTalk.Protocol.Responses
{
    public enum SendMessageResult
    {
        Ok,
        UserNotFound,
    }

    public class SendMessageResponse : ResponseBase
    {
        public SendMessageResponse(SendMessageResult result)
        {
            Result = result;
        }

        public override ResponseType ResponseType { get; } = ResponseType.SendMessage;

        public SendMessageResult Result { get; private set; }

        public static SendMessageResponse Parse(byte[] bytes)
        {
            using (MemoryStream stream = new MemoryStream(bytes))
            using (BinaryReader reader = new BinaryReader(stream, Encoding.ASCII))
            {
                ResponseType responseType = (ResponseType)reader.ReadInt32();
                if (responseType != ResponseType.SendMessage)
                    throw new InvalidOperationException("Invalid type of response");

                SendMessageResult result = (SendMessageResult)reader.ReadInt32();
                return new SendMessageResponse(result);
            }
        }
    }
}