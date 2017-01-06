namespace NetTalk.Protocol.Requests
{
    public class RegistrationRequest : AccountRequestBase
    {
        public RegistrationRequest(string userName, string password) : base(userName, password)
        {
        }

        public override RequestType RequestType { get; } = RequestType.Registration;
    }
}