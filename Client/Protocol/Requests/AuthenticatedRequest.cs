using System.IO;
using System.Text;

namespace NetTalk.Protocol.Requests
{
    public class AuthenticatedRequest : RequestBase
    {
        public AuthenticatedRequest(string authToken, RequestType requestType)
        {
            AuthToken = authToken;
            RequestType = requestType;
        }

        public string AuthToken { get; }
        public override RequestType RequestType { get; }

        public override byte[] ToBytes()
        {
            using (MemoryStream stream = new MemoryStream())
            using (BinaryWriter writer = new BinaryWriter(stream))
            {
                writer.Write((int)RequestType);
                writer.Write(AuthToken.Length);
                writer.Write(Encoding.ASCII.GetBytes(AuthToken));

                return stream.ToArray();
            }
        }
    }
}