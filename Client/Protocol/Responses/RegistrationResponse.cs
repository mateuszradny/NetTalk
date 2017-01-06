using System;
using System.IO;
using System.Text;

namespace NetTalk.Protocol.Responses
{
    public enum RegistrationResult
    {
        Ok,
        InvalidPassword,
        InvalidUserName,
        UserAlreadyExists,
    };

    public class RegistrationResponse : ResponseBase
    {
        public RegistrationResponse(RegistrationResult result)
        {
            Result = result;
        }

        public override ResponseType ResponseType { get; } = ResponseType.RegistrationResult;
        public RegistrationResult Result { get; private set; }

        public static RegistrationResponse Parse(byte[] bytes)
        {
            using (MemoryStream stream = new MemoryStream(bytes))
            using (BinaryReader reader = new BinaryReader(stream, Encoding.ASCII))
            {
                ResponseType responseType = (ResponseType)reader.ReadInt32();
                if (responseType != ResponseType.RegistrationResult)
                    throw new InvalidOperationException("Invalid type of response");

                RegistrationResult result = (RegistrationResult)reader.ReadInt32();
                return new RegistrationResponse(result);
            }
        }
    }
}