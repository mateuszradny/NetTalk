namespace NetTalk.Protocol.Requests
{
    public class ReceiveMessagesRequest : AuthenticatedRequest
    {
        public ReceiveMessagesRequest(string authToken) : base(authToken, RequestType.ReceiveMessages)
        {
        }
    }
}