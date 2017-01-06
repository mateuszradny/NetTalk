using MaterialDesignThemes.Wpf;
using System;
using System.Globalization;
using System.Windows.Data;
using System.Windows.Markup;

namespace NetTalk.ValueConverters
{
    public class BooleanToIconKindConverter : MarkupExtension, IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            return ((bool)value) ? PackIconKind.Account : PackIconKind.AccountOff;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            return null;
        }

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return this;
        }
    }
}