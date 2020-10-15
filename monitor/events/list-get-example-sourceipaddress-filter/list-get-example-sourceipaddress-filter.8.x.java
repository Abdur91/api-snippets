// Install the Java helper library from twilio.com/docs/java/install
import com.twilio.Twilio;
import com.twilio.base.ResourceSet;
import com.twilio.rest.monitor.v1.Event;

import java.time.LocalDate;

public class Example {
  /// Find your Account Sid and Token at twilio.com/user/account
  public static final String ACCOUNT_SID = "ACXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
  public static final String AUTH_TOKEN = "your_auth_token";

  public static void main(String[] args) {
    Twilio.init(ACCOUNT_SID, AUTH_TOKEN);

    ResourceSet<Event> events = Event.reader()
        .setSourceIpAddress("104.14.155.29")
        .setStartDate(LocalDate.of(2015, 4, 25))
        .setEndDate(LocalDate.of(2015, 4, 25))
        .read();

    for (Event e : events) {
      System.out.println(e.getDescription());
    }
  }
}
