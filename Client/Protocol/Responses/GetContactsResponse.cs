using NetTalk.Model;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace NetTalk.Protocol.Responses
{
    public class GetContactsResponse : ResponseBase
    {
        public GetContactsResponse(List<Contact> contacts)
        {
            Contacts = contacts;
        }

        public List<Contact> Contacts { get; }
        public override ResponseType ResponseType { get; } = ResponseType.AddContact;

        public static GetContactsResponse Parse(byte[] bytes)
        {
            using (MemoryStream stream = new MemoryStream(bytes))
            using (BinaryReader reader = new BinaryReader(stream))
            {
                ResponseType responseType = (ResponseType)reader.ReadInt32();
                if (responseType != ResponseType.GetContacts)
                    throw new InvalidOperationException("Invalid type of response");

                int contactCount = reader.ReadInt32();
                List<Contact> contacts = new List<Contact>();
                for (int i = 0; i < contactCount; i++)
                {
                    Contact contact = new Contact();

                    contact.Name = Encoding.ASCII.GetString(reader.ReadBytes(reader.ReadInt32()));
                    contact.IsOnline = reader.ReadBoolean();

                    contacts.Add(contact);
                }

                return new GetContactsResponse(contacts);
            }
        }
    }
}