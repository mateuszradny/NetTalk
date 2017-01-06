namespace NetTalk.Protocol.Responses
{
    public enum ResponseType
    {
        InvalidAuthToken = -2,
        ServerError = -1,
        Ok = 0,
        RegistrationResult = 1,
        LoginResult = 2,
        AddContact = 3,
        GetContacts = 4,
        SendMessage = 5,
        ReceiveMessages = 6,
    }

    public abstract class ResponseBase
    {
        public abstract ResponseType ResponseType { get; }
    }
}