#include <gtest/gtest.h>

#include <switch-mock.h>
#include <sensor-mock.h>
#include <display-led-stripe.h>

#include <vector>

TEST(display_led_stripe_suite, movement)
{
    MockSensor sensor(36.5);                    // <--- initially in the middle
    MockSwitch sw0(MockSwitch::OFF);
    MockSwitch sw1(MockSwitch::OFF);
    MockSwitch sw2(MockSwitch::OFF);
    MockSwitch sw3(MockSwitch::OFF);
    MockSwitch sw4(MockSwitch::OFF);
    MockSwitch sw5(MockSwitch::OFF);
    MockSwitch sw6(MockSwitch::OFF);
    MockSwitch sw7(MockSwitch::OFF);

    std::vector<MockSwitch*> switches = { &sw0, &sw1, &sw2, &sw3, &sw4, &sw5, &sw6, &sw7 };
    LEDStripeDisplay display(
        0, 80,                                         // <--- [0,80]
        &sensor, switches);

    display.check();

    ASSERT_EQ(sw0.state(), MockSwitch::ON);
    ASSERT_EQ(sw1.state(), MockSwitch::ON);
    ASSERT_EQ(sw2.state(), MockSwitch::ON);
    ASSERT_EQ(sw3.state(), MockSwitch::ON);
    ASSERT_EQ(sw4.state(), MockSwitch::OFF);
    ASSERT_EQ(sw5.state(), MockSwitch::OFF);
    ASSERT_EQ(sw6.state(), MockSwitch::OFF);
    ASSERT_EQ(sw7.state(), MockSwitch::OFF);

    sensor.set_temperature(67);                        // <--- temperature moves into segment [60,70]

    display.check();

    ASSERT_EQ(sw0.state(), MockSwitch::ON);
    ASSERT_EQ(sw1.state(), MockSwitch::ON);
    ASSERT_EQ(sw2.state(), MockSwitch::ON);
    ASSERT_EQ(sw3.state(), MockSwitch::ON);
    ASSERT_EQ(sw4.state(), MockSwitch::ON);
    ASSERT_EQ(sw5.state(), MockSwitch::ON);
    ASSERT_EQ(sw6.state(), MockSwitch::ON);
    ASSERT_EQ(sw7.state(), MockSwitch::OFF);

    sensor.set_temperature(9);                         // <--- back down into [0,10]

    display.check();

    ASSERT_EQ(sw0.state(), MockSwitch::ON);
    ASSERT_EQ(sw1.state(), MockSwitch::OFF);
    ASSERT_EQ(sw2.state(), MockSwitch::OFF);
    ASSERT_EQ(sw3.state(), MockSwitch::OFF);
    ASSERT_EQ(sw4.state(), MockSwitch::OFF);
    ASSERT_EQ(sw5.state(), MockSwitch::OFF);
    ASSERT_EQ(sw6.state(), MockSwitch::OFF);
    ASSERT_EQ(sw7.state(), MockSwitch::OFF);

    sensor.set_temperature(-10);                       // <--- below range -> all off

    display.check();

    ASSERT_EQ(sw0.state(), MockSwitch::OFF);
    ASSERT_EQ(sw1.state(), MockSwitch::OFF);
    ASSERT_EQ(sw2.state(), MockSwitch::OFF);
    ASSERT_EQ(sw3.state(), MockSwitch::OFF);
    ASSERT_EQ(sw4.state(), MockSwitch::OFF);
    ASSERT_EQ(sw5.state(), MockSwitch::OFF);
    ASSERT_EQ(sw6.state(), MockSwitch::OFF);
    ASSERT_EQ(sw7.state(), MockSwitch::OFF);
}
