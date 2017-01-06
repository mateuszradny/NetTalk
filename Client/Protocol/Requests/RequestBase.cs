namespace NetTalk.Protocol.Requests
{
    public enum RequestType
    {
        Registration,
        Login,
        AddContact,
        GetContacts,
        RemoveContact,
        SendMessage,
        ReceiveMessages,
        Logout
    }

    public abstract class RequestBase
    {
        public abstract RequestType RequestType { get; }

        public abstract byte[] ToBytes();
    }
}