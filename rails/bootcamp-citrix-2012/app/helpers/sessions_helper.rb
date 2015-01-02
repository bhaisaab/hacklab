module SessionsHelper

  def get_gravatar(email, size=32)
    hash = Digest::MD5.hexdigest(email.downcase)
    return "http://www.gravatar.com/avatar/#{hash}?s=#{size}"
  end

end
