using System;

namespace NetTalk.Model
{
    public enum MessageDirection
    {
        Incoming,
        Outgoing,
    }

    public class Message
    {
        public string Body { get; set; }
        public DateTime PostDate { get; set; }
        public string Sender { get; set; }
        public MessageDirection Direction { get; set; }
    }
}