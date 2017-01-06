using System;
using System.IO;
using System.Text;

namespace NetTalk.Protocol.Requests
{
    public class AddContactRequest : AuthenticatedRequest
    {
        public AddContactRequest(string authToken, string contactName) : base(authToken, RequestType.AddContact)
        {
            if (string.IsNullOrWhiteSpace(contactName))
                throw new ArgumentException(nameof(contactName));

            ContactName = contactName;
        }

        public string ContactName { get; private set; }

        public override byte[] ToBytes()
        {
            using (MemoryStream stream = new MemoryStream())
            using (BinaryWriter writer = new BinaryWriter(stream))
            {
                writer.Write((int)RequestType);
                writer.Write(AuthToken.Length);
                writer.Write(Encoding.ASCII.GetBytes(AuthToken));
                writer.Write(ContactName.Length);
                writer.Write(Encoding.ASCII.GetBytes(ContactName));

                return stream.ToArray();
            }
        }
    }
}