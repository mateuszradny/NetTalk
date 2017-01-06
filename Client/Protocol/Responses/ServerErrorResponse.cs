using System;
using System.IO;
using System.Text;

namespace NetTalk.Protocol.Responses
{
    public class ServerErrorResponse : ResponseBase
    {
        public ServerErrorResponse(string errorMessage)
        {
            ErrorMessage = errorMessage;
        }

        public string ErrorMessage { get; private set; }
        public override ResponseType ResponseType { get; } = ResponseType.ServerError;

        public static ServerErrorResponse Parse(byte[] bytes)
        {
            using (MemoryStream stream = new MemoryStream(bytes))
            using (BinaryReader reader = new BinaryReader(stream, Encoding.ASCII))
            {
                ResponseType responseType = (ResponseType)reader.ReadInt32();
                if (responseType != ResponseType.ServerError)
                    throw new InvalidOperationException("Invalid type of response");

                string errorMessage = Encoding.ASCII.GetString(reader.ReadBytes(reader.ReadInt32()));
                return new ServerErrorResponse(errorMessage);
            }
        }
    }
}