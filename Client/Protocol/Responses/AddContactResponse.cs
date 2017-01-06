using System;
using System.IO;

namespace NetTalk.Protocol.Responses
{
    public enum AddContactResult
    {
        Ok,
        UserNotFound,
    };

    public class AddContactResponse : ResponseBase
    {
        public AddContactResponse(AddContactResult result)
        {
            Result = result;
        }

        public override ResponseType ResponseType { get; } = ResponseType.AddContact;
        public AddContactResult Result { get; private set; }

        public static AddContactResponse Parse(byte[] bytes)
        {
            using (MemoryStream stream = new MemoryStream(bytes))
            using (BinaryReader reader = new BinaryReader(stream))
            {
                ResponseType responseType = (ResponseType)reader.ReadInt32();
                if (responseType != ResponseType.AddContact)
                    throw new InvalidOperationException("Invalid type of response");

                AddContactResult result = (AddContactResult)reader.ReadInt32();

                return new AddContactResponse(result);
            }
        }
    }
}