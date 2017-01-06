namespace NetTalk.Protocol.Requests
{
    public class LoginRequest : AccountRequestBase
    {
        public LoginRequest(string userName, string password) : base(userName, password)
        {
        }

        public override RequestType RequestType { get; } = RequestType.Login;
    }
}