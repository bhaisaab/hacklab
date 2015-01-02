class User < ActiveRecord::Base
  attr_accessible :email, :name, :website

  validates_uniqueness_of :email
  email_regex = /\A[\w+\-.]+@[a-z\d\-.]+\.[a-z]+\z/i

  validates :name,  :presence => true,
                    :length   => { :maximum => 40 }

  validates :email, :presence => true,
                    :format   => { :with => email_regex },
                    :uniqueness => { :case_sensitive => false }

  has_many :bookings, :dependent => :destroy
end
