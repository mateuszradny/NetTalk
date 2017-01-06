using System;
using System.IO;
using System.Text;

namespace NetTalk.Protocol.Requests
{
    public abstract class AccountRequestBase : RequestBase
    {
        public AccountRequestBase(string userName, string password)
        {
            if (string.IsNullOrWhiteSpace(userName))
                throw new ArgumentException("Invalud user name", nameof(userName));

            if (string.IsNullOrWhiteSpace(password))
                throw new ArgumentException("Invalid password", nameof(password));

            this.UserName = userName;
            this.Password = password;
        }

        public string Password { get; private set; }
        public string UserName { get; private set; }

        public override byte[] ToBytes()
        {
            using (MemoryStream stream = new MemoryStream())
            using (BinaryWriter writer = new BinaryWriter(stream))
            {
                writer.Write((int)RequestType);
                writer.Write(UserName.Length);
                writer.Write(Encoding.ASCII.GetBytes(UserName));
                writer.Write(Password.Length);
                writer.Write(Encoding.ASCII.GetBytes(Password));

                return stream.ToArray();
            }
        }
    }
}