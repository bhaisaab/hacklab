class BookingMailer < ActionMailer::Base
  default :from => "rohityadav89@gmail.com"

  def welcome_email(email)
    mail(:to => email, :subject => "It works")
  end
end
