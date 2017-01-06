using System;
using System.IO;
using System.Text;

namespace NetTalk.Protocol.Responses
{
    public enum LoginResult
    {
        Ok,
        InvalidCredentials,
    };

    public class LoginResponse : ResponseBase
    {
        public LoginResponse(LoginResult result, string authToken)
        {
            Result = result;
            AuthToken = authToken;
        }

        public string AuthToken { get; private set; }
        public override ResponseType ResponseType { get; } = ResponseType.LoginResult;
        public LoginResult Result { get; private set; }

        public static LoginResponse Parse(byte[] bytes)
        {
            using (MemoryStream stream = new MemoryStream(bytes))
            using (BinaryReader reader = new BinaryReader(stream))
            {
                ResponseType responseType = (ResponseType)reader.ReadInt32();
                if (responseType != ResponseType.LoginResult)
                    throw new InvalidOperationException("Invalid type of response");

                LoginResult result = (LoginResult)reader.ReadInt32();
                string authToken = Encoding.ASCII.GetString(reader.ReadBytes(reader.ReadInt32()));

                return new LoginResponse(result, authToken);
            }
        }
    }
}