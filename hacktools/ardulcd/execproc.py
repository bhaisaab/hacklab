import subprocess

class Monitor(object):
  def __init__(self, username):
    """Create new MemoryMonitor instance."""
    self.username = username

  def run(self, cmd):
    """Return int containing memory used by user's processes."""
    self.process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
    self.stdout_list = self.process.communicate()[0].split('\n')
    return self.stdout_list[0]

